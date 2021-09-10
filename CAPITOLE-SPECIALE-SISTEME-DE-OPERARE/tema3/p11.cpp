#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

#define BUF_SIZE 10000
#define FMAP_NAME "fComm"
#define MTX_NAME "mName"
#define ITERATIONS 300

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
		FMAP_NAME);              // name of mapping object
	if (hMapFile == NULL)
	{
		cout << "Could not create file mapping object: " << GetLastError() << "\n";
		return 1;
	}

	// creez o referinta la fisier
	char* pBuf = (char*)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_WRITE, // read/write permission
		0,
		0,
		0);

	if (pBuf == NULL)
	{
		cout << "Could not map view of file: " << GetLastError() << "\n";

		CloseHandle(hMapFile);
		return 1;
	}

	// creez mutex-ul
	HANDLE hMutex = CreateMutex(
		NULL,
		FALSE,
		MTX_NAME
	);
	if (hMutex == NULL)
	{
		cout << "Could not create mutex: " << GetLastError() << "\n";
		return 1;
	}

	srand(time(NULL));

	// lansez al doilea program
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	if (!CreateProcess("D:\\Diverse\\Facultate\\csso\\tema3\\ConsoleApplication2\\Debug\\ConsoleApplication2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		printf("Cannot create process.\n");
		return 0;
	}
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	// scriu in fisier
	for (int i = 0; i < ITERATIONS; i++)
	{
		// generez a, calculez b=2a
		int a = rand() % 1000;
		int b = 2 * a;


		string numbers = to_string(a) + " " + to_string(b);

		// stabileste sincronizarea
		if (WaitForSingleObject(hMutex, INFINITE) == 0)
		{
			cout << a << " " << b << "\n";

			strcpy(pBuf, numbers.c_str());
		
			ReleaseMutex(hMutex);
		}

	}
	
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	CloseHandle(hMutex);
	
	return 0;
}