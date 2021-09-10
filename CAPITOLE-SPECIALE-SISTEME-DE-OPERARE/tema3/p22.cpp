#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string> 

#define BUF_SIZE 10000
#define FMAP_NAME "fComm"
#define EVN_WRITE "eWrite"
#define EVN_READ "eRead"
#define ITERATIONS 300

using namespace std;

int main()
{
    // accesez fisierul mapat in memorie
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_READ,   // read/write access
        FALSE,                 // do not inherit the name
        FMAP_NAME);               // name of mapping object

    if (hMapFile == NULL)
    {
        cout << "Could not open file mapping object: " << GetLastError() << "\n";
        return 1;
    }

    // preiau referinta la fisier
    char* pBuf = (char*)MapViewOfFile(hMapFile, // handle to map object
        FILE_MAP_READ,  // read/write permission
        0,
        0,
        0);

    if (pBuf == NULL)
    {
        cout << "Could not map view of file: " << GetLastError() << "\n";

        CloseHandle(hMapFile);
        return 1;
    }

    // obtin accesul la event-uri
    HANDLE hWrite = OpenEvent(
        SYNCHRONIZE | EVENT_MODIFY_STATE,
        FALSE,
        EVN_WRITE
    );
    if (hWrite == NULL)
    {
        cout << "Could not open write event: " << GetLastError() << "\n";
        return 1;
    }

    HANDLE hRead = OpenEvent(
        SYNCHRONIZE | EVENT_MODIFY_STATE,
        FALSE,
        EVN_READ
    );
    if (hRead == NULL)
    {
        cout << "Could not open read event: " << GetLastError() << "\n";
        return 1;
    }

    for (int i = 0; i < ITERATIONS; i++)
    {
        
        if (WaitForSingleObject(hRead, INFINITE) == 0)
        {
            stringstream numbers(pBuf);
            int a, b;
            numbers >> a >> b;
            
            cout << a << " " << b << " -> " << (b == 2 * a ? "correct" : "incorrect") << "\n";
            
            SetEvent(hWrite);
        }

    }
    
    CloseHandle(hMapFile);
    CloseHandle(hWrite);
    CloseHandle(hRead);
    
    return 0;
}