#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define BUF_SIZE 10000
#define FMAP_NAME "myProcEnum"

using namespace std;

int main()
{
	// mapez fisierul in memorie
	HANDLE hMapFile;
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		FMAP_NAME);                 // name of mapping object
	if (hMapFile == NULL)
	{
		cout << "Could not create file mapping object: " << GetLastError() << "\n";
		return 1;
	}

	// creez o referinta la fisier
	char* pBuf = (char*)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		0);

	if (pBuf == NULL)
	{
		cout << "Could not map view of file: " << GetLastError() << "\n";

		CloseHandle(hMapFile);
		return 1;
	}

	PROCESSENTRY32 pe32;
	//cer un snapshot la procese
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return 1;
	}
	// initializez dwSize cu dimensiunea structurii.
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// obtin informatii despre primul proces
	if (!Process32First(hProcessSnap, &pe32))
	{
		printf("Process32First failed. err = %d \n", GetLastError());
		CloseHandle(hProcessSnap); 
		return 1;
	}

	string shared_msg = "";
	// preiau pid-ul, ppid-ul si exef-ul fiecarui proces si concatenez la "shared_msg"
	do
	{
		int pid = pe32.th32ProcessID;
		int ppid = pe32.th32ParentProcessID;
		string ef = pe32.szExeFile;

		// delimitez fiecare informatie cu un ";" pt parsare
		string s_pid = to_string(pid) + ";";
		string s_ppid = to_string(ppid) + ";";
		string s_ef = ef + ";";

		// concatenez
		shared_msg = shared_msg + s_pid + s_ppid + s_ef;

		cout << pid << " " << ef << ", child of " << ppid << "\n";
	} while (Process32Next(hProcessSnap, &pe32)); // iterez prin procese
	CloseHandle(hProcessSnap);

	strcpy(pBuf, shared_msg.c_str());

	cout << "Press any key to terminate the process.";
	char c = _getch();

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);

	return 0;
}