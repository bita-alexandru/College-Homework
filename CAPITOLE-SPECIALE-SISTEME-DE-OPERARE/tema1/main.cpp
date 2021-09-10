#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <map>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define LOG(x) std::cout << x << '\n'

void ReadQuery(HKEY hive, LPCSTR cwd, LPCSTR path)
{
    DWORD i, retCode;
    HKEY hKey;
    if (RegOpenKeyEx(hive,
        cwd,
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS
        )
    {
        std::cout << '\n' << "[OPENING REGISTRY] " << cwd << '\n';
    }
    else
    {
        LOG("...REGISTRY KEY DOES NOT EXIST");
    }

    // Create the directory
    std::cout << "[CREATING DIRECTORY] " << path << '\n';
    retCode = CreateDirectory(path, NULL);
    if (retCode != 0)
    {
        LOG("...SUCCESS");
    }
    else if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        LOG("...ALREADY EXISTS");
    }
    else if (GetLastError() == ERROR_PATH_NOT_FOUND)
    {
        LOG("...PATH NOT FOUND");
    }

    TCHAR achKey[MAX_KEY_LENGTH];
    DWORD cbName;
    DWORD cSubKeys = 0;
    DWORD cbMaxSubKey;
    DWORD cValues;
    DWORD cchMaxValue;

    TCHAR achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the registry's metadata
    retCode = RegQueryInfoKey(
        hKey, 
        NULL,
        NULL, 
        NULL, 
        &cSubKeys, 
        &cbMaxSubKey, 
        NULL,
        &cValues,
        &cchMaxValue, 
        NULL,
        NULL, 
        NULL);

    // Read through the subkeys recursively
    if (cSubKeys)
    {
        for (i = 0; i < cSubKeys; i++)
        {
            cbName = cbMaxSubKey + 1;
            retCode = RegEnumKeyEx(hKey, i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                NULL);
            if (retCode == ERROR_SUCCESS)
            {
                std::string cwdNew = (std::string(cwd) + std::string("\\") + std::string(achKey));
                std::string pathNew = (std::string(path) + std::string("\\") + std::string(achKey));

                ReadQuery(hive, cwdNew.c_str(), pathNew.c_str());
            }
        }
    }

    // Read through the values and create the files 
    if (cValues)
    {
        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
        {
            cchValue = cchMaxValue + 1;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
                // Create a file with the name corresponding to the value
                std::string pathNew = (std::string(path) + std::string("\\") + std::string(achValue));

                std::cout << "[CREATING FILE] " << pathNew << '\n';
                HANDLE file = CreateFile(pathNew.c_str(),
                    GENERIC_WRITE,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
                if (file == INVALID_HANDLE_VALUE)
                {
                    LOG("...HANDLE DOES NOT EXIST");
                }
                else
                {
                    LOG("...SUCCESS");
                }
            }
        }
    }

    RegCloseKey(hKey);
}

int __cdecl _tmain()
{
    std::string cwd;
    std::cout << "Registry Key: ";
    std::cin >> cwd;

    std::map<std::string, HKEY> hives = { {"HKEY_LOCAL_MACHINE",HKEY_LOCAL_MACHINE},
                                            {"HKEY_CURRENT_CONFIG",HKEY_CURRENT_CONFIG},
                                            {"HKEY_CLASSES_ROOT",HKEY_CLASSES_ROOT },
                                            {"HKEY_CURRENT_USER",HKEY_CURRENT_USER},
                                            {"HKEY_USERS",HKEY_USERS},
                                            {"HKEY_PERFORMANCE_DATA",HKEY_PERFORMANCE_DATA},
                                            {"HKEY_DYN_DATA",HKEY_DYN_DATA}
    };
    std::string hiveToken = cwd.substr(0, cwd.find("\\"));
    HKEY hive = hives[hiveToken];

    std::size_t pos = 0;
    std::string path = cwd;
    while ((pos = path.find("\\")) != std::string::npos)
    {
        path.erase(0, pos + 1);
    }
    path = "D:\\" + path;
    cwd.erase(0, cwd.find("\\") + 1);

    ReadQuery(hive, cwd.c_str(), path.c_str());
}