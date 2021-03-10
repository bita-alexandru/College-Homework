#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#define PORT "2405"
#define BUFF 512

#define err(x, e) { cout << x << e << "\n";}

using namespace std;

typedef struct MyData {
    sockaddr* client;
    char command[BUFF];
    char filename[BUFF];
    char text[BUFF];
} MYDATA, * PMYDATA;

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

    sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serverSocket.sin_addr.s_addr);
    serverSocket.sin_port = htons(2405);
    int serverLength = sizeof(serverSocket);

    char availableComms[8][BUFF] = {
        "createfile", "appendfile", "deletefile", "createreg", "deletereg", "runprocess", "download", "listdir"
    };

    cout << "Available commands:\n";
    for (int i = 0; i < 8; i++) {
        cout << "    " << availableComms[i] << '\n';
    }
    cout << '\n';
    cout << "Utility commands:\n    help\n    clear | clr\n\n";


    while (true) {
        char command[BUFF / 3 - 1] = { 0 };
        cout << "> command: ";
        std::fgets(command, BUFF / 3-1, stdin);
        command[strlen(command) - 1] = '\0';

        if (strstr("clear clr", command)) {
            system("cls");
            cout << "Available commands:\n";
            for (int i = 0; i < 8; i++) {
                cout << "    " << availableComms[i] << '\n';
            }
            cout << '\n';
            cout << "Utility commands:\n    help\n    clear | clr\n\n";

            continue;
        }
        if (!strcmp("help", command)) {
            cout << "Available commands:\n";
            for (int i = 0; i < 8; i++) {
                cout << "   " << availableComms[i] << '\n';
            }
            cout << '\n';
            cout << "Utility commands:\n    help\n    clear | clr\n\n";

            continue;
        }

        bool ok = false;
        for (int i = 0; i < 8; i++) {
            if (!strcmp(command, availableComms[i])) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << "Invalid syntax.\n";
            continue;
        }

        if (strstr("createfile appendfile deletefile", command)) {
            cout << "> filename: ";
        }
        else if (strstr("createreg deletereg", command)) {
            cout << "> registry-location: ";
        }
        else if (strstr("runprocess", command)) {
            cout << "> process-location: ";
        }
        else if (strstr("download", command)) {
            cout << "> url: ";
        }
        else {
            cout << "> directory-location: ";
        }

        char path[BUFF / 3 - 1] = { 0 };
        std::fgets(path, BUFF / 3 - 1, stdin);
        path[strlen(path) - 1] = '\0';

        char text[BUFF / 3 - 1] = { 0 };
        if (!strcmp(command, "appendfile")) {
            cout << "> text: ";
            std::fgets(text, BUFF / 3 - 1, stdin);
        }

        string str = command + string("#") + path + string("#") + text;

        int nSent = sendto(Socket, str.c_str(), BUFF, 0, (struct sockaddr*)&serverSocket, sizeof(serverSocket));
        if (nSent == SOCKET_ERROR) {
            err("Failed at sendto(): ", GetLastError());
            continue;
        }

        cout << "[REQUEST SENT]" << "\n";
    }
}