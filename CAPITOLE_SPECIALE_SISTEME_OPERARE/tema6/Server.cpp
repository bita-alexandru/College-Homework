#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <WinInet.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wininet") 
#define PORT "2405"
#define BUFF 512
#define SIZE 8192

#define err(x, e) { cout << x << e << "\n";}

using namespace std;

typedef struct MyData {
    sockaddr_in* client;
    char command[BUFF];
    char path[BUFF];
    char text[BUFF];
} MYDATA, *PMYDATA;

bool opFile(int command, string filename, string text) {
    switch (command) {
    case 0: {
        HANDLE file = CreateFile(filename.c_str(),
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (file == INVALID_HANDLE_VALUE) {
            return false;
        }
        else {
            CloseHandle(file);
            return true;
        }
    }
    case 1: {
        HANDLE file = CreateFile(filename.c_str(),
            FILE_APPEND_DATA,
            0,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (file == INVALID_HANDLE_VALUE) {
            return false;
        }
        else {
            DWORD nWritten = 0;
            WriteFile(file, text.c_str(), text.size(), &nWritten, NULL);
            if (!nWritten) {
                CloseHandle(file);
                return false;
            }
            CloseHandle(file);
            return true;
        }
    }
    case 2:
        if (DeleteFile(filename.c_str())) {
            return true;
        }
        return false;
    default:
        return false;
    }
}

bool opReg(int command, string regname) {
    map<string, HKEY> hives = { {"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
                                {"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
                                {"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT },
                                {"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
                                {"HKEY_USERS", HKEY_USERS},
                                {"HKEY_PERFORMANCE_DATA", HKEY_PERFORMANCE_DATA},
                                {"HKEY_DYN_DATA", HKEY_DYN_DATA}
    };
    string hiveToken = regname.substr(0, regname.find("\\"));
    HKEY hive = hives[hiveToken];
    regname.erase(0, regname.find("\\") + 1);

    switch (command) {
    case 0: {
        HKEY reg;
        DWORD disp;

        if (!RegCreateKeyEx(
            hive, regname.c_str(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, &disp
        )) {
            RegCloseKey(reg);
            return true;
        }
        return false;
    }
    case 1: {
        HKEY reg;
        reverse(regname.begin(), regname.end());

        string subkey = "";
        if(regname.find("\\") != string::npos) {
            subkey = regname.substr(0, regname.find("\\"));
            regname.erase(0, regname.find("\\") + 1);
            reverse(regname.begin(), regname.end());
            reverse(subkey.begin(), subkey.end());
        }
        else {
            subkey = regname;
            reverse(subkey.begin(), subkey.end());
            regname = "";
        }
        
        if (!RegOpenKeyEx(hive, regname.c_str(), 0, KEY_ALL_ACCESS, &reg)) {
            if (!RegDeleteKey(reg, subkey.c_str())) {
                RegCloseKey(reg);
                return true;
            }
            RegCloseKey(reg);
            return false;
        }
        return false;
    }
    default:
        return false;
    }
}

bool opRun(string process) {
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    BOOL createProcess = CreateProcess(
        process.c_str(),
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    );
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    if (!createProcess)
    {
        return false;
    }
    return true;
}

bool opDownload(string url) {
    while (url.size() && url[url.size() - 1] == '/') {
        url.pop_back();
    }

    HINTERNET hInternet = InternetOpen(
        "Alex",
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL,
        NULL,
        NULL
    );
    if (!hInternet) {
        return false;
    }

    if (url.find(":") != string::npos) {
        url.erase(0, url.find(":") + 3);
    }

    string domain = url.substr(0, url.find("/"));
    url.erase(0, url.find("/") + 1);

    HINTERNET hConnect = InternetConnect(
        hInternet,
        domain.c_str(),
        80,
        NULL,
        NULL,
        INTERNET_SERVICE_HTTP,
        NULL,
        NULL
    );
    if (hConnect == NULL) {
        return false;
    }

    const char* acceptTypes[] = { "text/*", NULL };
    HINTERNET hOpenRequest = HttpOpenRequest(
        hConnect,
        "GET",
        url.c_str(),
        "1.1",
        NULL,
        acceptTypes,
        NULL,
        NULL
    );
    if (hOpenRequest == NULL) {
        return false;
    }

    BOOL sendRequest = HttpSendRequest(hOpenRequest, NULL, NULL, NULL, NULL);
    if (!sendRequest) {
        return false;
    }

    while (url.find("/") != string::npos) {
        url.erase(0, url.find("/") + 1);
    }
    opFile(2, url, "");

    DWORD sizeRead;
    do {
        char buf[SIZE] = {0};
        BOOL readFile = InternetReadFile(
            hOpenRequest,
            buf,
            SIZE,
            &sizeRead
        );
        if (!readFile) {
            return false;
        }

        if (sizeRead && !opFile(1, url, buf)) {
            return false;
        }
    } while (sizeRead);

    return true;
}

bool opListDir(string dir, int indent) {
    WIN32_FIND_DATA findData;
    HANDLE findFirst = FindFirstFile((dir + string("\\*")).c_str(), &findData);

    if (findFirst == INVALID_HANDLE_VALUE) {
        return false;
    }

    do {
        if (!strcmp(findData.cFileName, ".") || !strcmp(findData.cFileName, "..")) {
            continue;
        }

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            for (int i = 0; i < indent; i++) {
                cout << " ";
            }

            cout << findData.cFileName << '\n';
            opListDir(dir + (string("\\") + findData.cFileName), indent + 4);
        }
        else {
            for (int i = 0; i < indent; i++) {
                cout << " ";
            }

            cout << findData.cFileName << '\n';
        }

    } while (FindNextFile(findFirst, &findData));

    return true;
}

DWORD WINAPI threadFunction(LPVOID lpParam) {
    PMYDATA pData = (PMYDATA)lpParam;
    cout << "[NEW REQUEST]\n";

    cout << "--- input ---\n";
    cout << "command: " << pData->command << '\n';
    cout << "path: " << pData->path << '\n';
    cout << "text: " << pData->text << '\n';
    cout << "--- output ---\n";

    bool succeed = false;

    if (!strcmp(pData->command, "createfile")) {
        succeed = opFile(0, pData->path, "");

        if (succeed) {
            cout << "<createfile success>" << "\n";
        }
        else {
            cout << "<createfile failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "appendfile")) {
        succeed = opFile(1, pData->path, pData->text);

        if (succeed) {
            cout << "<appendfile success>" << "\n";
        }
        else {
            cout << "<appendfile failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "deletefile")) {
        succeed = opFile(2, pData->path, "");

        if (succeed) {
            cout << "<deletefile success>" << "\n";
        }
        else {
            cout << "<deletefile failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "createreg")) {
        succeed = opReg(0, pData->path);

        if (succeed) {
            cout << "<createreg success>" << "\n";
        }
        else {
            cout << "<createreg failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "deletereg")) {
        succeed = opReg(1, pData->path);

        if (succeed) {
            cout << "<deletereg success>" << "\n";
        }
        else {
            cout << "<deletereg failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "runprocess")) {
        succeed = opRun(pData->path);

        if (succeed) {
            cout << "<runprocess success>" << "\n";
        }
        else {
            cout << "<runprocess failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "download")) {
        succeed = opDownload(pData->path);

        if (succeed) {
            cout << "<download success>" << "\n";
        }
        else {
            cout << "<download failed>" << "\n";
        }
    }
    else if (!strcmp(pData->command, "listdir")) {
        succeed = opListDir(pData->path, 0);

        if (succeed) {
            cout << "<listdir success>" << "\n";
        }
        else {
            cout << "<listdir failed>" << "\n";
        }
    }

    cout << "\n";

    HeapFree(GetProcessHeap(), 0, pData);
    return 0;
}

int main()
{
    WSADATA wsaData;

    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        err("Failed at WSAStartup(): ", iResult);
        return -1;
    }

    // Creating socket
    SOCKET Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket == INVALID_SOCKET) {
        err("Failed at socket(): ", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    sockaddr_in server;
    server.sin_addr.S_un.S_addr = ADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(2405);

    // Setup the UDP listening socket
    if (bind(Socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cout << "Can't bind to the socket! " << WSAGetLastError() << endl;
        return -1;
    }

    while (true) {
        char buf[BUFF] = { 0 };
        sockaddr_in clientSocket = { 0 };
        int clientLength = sizeof(clientSocket);

        int nRead = recvfrom(Socket, buf, BUFF, 0, (struct sockaddr*)&clientSocket, &clientLength);
        if (nRead == SOCKET_ERROR) {
            err("Failed at recvfrom(): ", WSAGetLastError());
            return -1;
        }
        
        string str = buf;
        stringstream ss(str);
        string command, filename, text = "";
        getline(ss, command, '#');
        getline(ss, filename, '#');
        if (command == "appendfile") {
            getline(ss, text, '\n');
        }

        PMYDATA pData = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
        if (!pData) {
			err("Failed at HeapAlloc() :", GetLastError());
            return -1;
        }
        pData->client = &clientSocket;
        std::strcpy(pData->command, command.c_str());
        std::strcpy(pData->path, filename.c_str());
        std::strcpy(pData->text, text.c_str());
        
        DWORD threadId;
        HANDLE hThread = CreateThread(
            NULL,
            0,
            threadFunction,
            pData,
            0,
            &threadId
        );

        if (!hThread) {
            err("Failed at CreateThread() :", GetLastError());
            return -1;
        }
    }
        
    closesocket(Socket);
    WSACleanup();

    return 0;
}

