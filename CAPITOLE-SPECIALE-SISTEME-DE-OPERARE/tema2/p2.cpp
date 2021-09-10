#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#define BUF_SIZE 10000
#define FMAP_NAME "myProcEnum"

using namespace std;

// o recursie care primeste nodul curent {nume,pid}, o lista cu copiii asociati lui(reprezentata printr-un dictionar/hashmap)
// si un parametru pentru indentare(cu cat mai adanc in arbore, cu atat mai multe spatii las la stanga)
void showTree(pair<string, int> node,
    map<pair<string, int>, vector<pair<string, int>>>& chldrn,
    int indent)
{
    for (int i = 1; i <= indent; i++)
    {
        std::cout << " ";
    }

    cout << node.first << " " << node.second << "\n";

    // niciun proces nu il are pe acesta ca parinte deci inchei functia
    if (chldrn.find(node) == chldrn.end())
    {
        return;
    }

    // altfel iterez prin copiii lui si fac recursie
    vector<pair<string, int>> children = chldrn[node];
    for (int i = 0; i < children.size(); i++)
    {
        showTree(children[i], chldrn, indent + 4);
    }
}

// asemanator cu showTree(), insa termin un proces doar dupa ce m-am asigurat ca nu are copii
void killTree(pair<string, int> node, map<pair<string, int>, vector<pair<string, int>>>& chldrn)
{
    if (chldrn.find(node) != chldrn.end())
    {
        vector<pair<string, int>> children = chldrn[node];
        for (int i = 0; i < children.size(); i++)
        {
            killTree(children[i], chldrn);
        }
    }

    cout << "Terminating process " << node.first << " " << node.second << "\n";

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, node.second);
    TerminateProcess(hProcess, NULL);

    CloseHandle(hProcess);
}

void showKillTrees(vector<int> &ancestors, map<int, string> &ancestors_names, map<pair<string, int>, vector<pair<string, int>>> &chldrn)
{
    bool terminated = false;

    while(!terminated)
    {
        // aici sunt doar procesele care nu au parinti deci reprezinta radacini de arbore
        for (int i = 0; i < ancestors.size(); i++)
        {
            cout << "[tree no. " << i + 1 << "]" << "\n";
            showTree({ ancestors_names[ancestors[i]], ancestors[i] }, chldrn, 4);
        }
        cout << "\n";

        while (true)
        {
            int option;
            cout << "Terminate a process tree (1" << "-" << ancestors.size() << ") or quit the program (-1): ";
            cin >> option;

            if (option == -1)
            {
                terminated = true;
                break;
            }
            else if (option >= 1 && option <= ancestors.size())
            {
                option--;
                killTree({ ancestors_names[ancestors[option]], ancestors[option] }, chldrn);
                ancestors.erase(ancestors.begin() + option);
                break;
            }
        }
    }
}

// citesc din fisierul mapat in memorie
void readFromMapping(char* pBuf)
{
    map<pair<string, int>, vector<pair<string, int>>> chldrn;
    map<int, string> ancestors_names;
    vector<int> ancestors;

    string msg = string(pBuf);
    stringstream ss(msg);

    int pid;
    int ppid;
    string ef;

    string s_tmp;
    stringstream ss_tmp;

    bool is_parsing = true;
    while (is_parsing)
    {
        // input-ul are forma "<pid>;<ppid>;<exef>;<pid>;<ppid>;<exef>;..."
        if (!getline(ss, s_tmp, ';'))
        {
            is_parsing = false;
            break;
        }
        ss_tmp.clear();
        ss_tmp.str(s_tmp);
        ss_tmp >> pid;

        if (!getline(ss, s_tmp, ';'))
        {
            is_parsing = false;
            break;
        }
        ss_tmp.clear();
        ss_tmp.str(s_tmp);
        ss_tmp >> ppid;

        if (!getline(ss, s_tmp, ';'))
        {
            is_parsing = false;
            break;
        }
        ss_tmp.clear();
        ss_tmp.str(s_tmp);
        ss_tmp >> ef;

        if (pid != 0)
        {
            // parintele nu apare in lista de procese, deci procesul la care sunt acum e radacina unui arbore
            if (ancestors_names.find(ppid) == ancestors_names.end())
            {
                ancestors.push_back(pid);
            }
            // parintele mai apare in lista de procese, deci acest proces reprezinta un fiu al parintelui intr-un arbore
            else
            {
                chldrn[{ancestors_names[ppid], ppid}].push_back({ ef, pid });
            }
            // marchez procesele prin care am trecut pana acum cu numele lor
            ancestors_names[pid] = ef;
        }
    }

    showKillTrees(ancestors, ancestors_names, chldrn);
}

int main()
{
    // accesez procesul curent
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        cout << "Could not open process token: " << GetLastError() << "\n";
        return 1;
    }

    // preiau referinta pt privilegiul "SE_DEBUG_NAME"
    LUID lpLuid;
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &lpLuid))
    {
        cout << "Could not identify process privilege: " << GetLastError() << "\n";

        CloseHandle(hToken);
        return 1;
    }

    // configurez structura de privilegii cu privilegiul "SE_DEBUG_NAME" setat
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = lpLuid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
    {
        cout << "Could not adjust process privilege: " <<  GetLastError() << "\n";

        CloseHandle(hToken);
        return 1;
    }

    // accesez fisierul mapat in memorie
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        FMAP_NAME);               // name of mapping object

    if (hMapFile == NULL)
    {
        cout << "Could not open file mapping object: " << GetLastError() << "\n";
        return 1;
    }

    // preiau referinta la fisier
    char* pBuf = (char*)MapViewOfFile(hMapFile, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        0);

    if (pBuf == NULL)
    {
        cout << "Could not map view of file: " << GetLastError() << "\n";

        CloseHandle(hMapFile);
        return 1;
    }

    readFromMapping(pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}