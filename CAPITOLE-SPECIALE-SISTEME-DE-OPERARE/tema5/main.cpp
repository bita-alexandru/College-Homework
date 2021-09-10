#include <Windows.h>
#include <AccCtrl.h>
#include <AclAPI.h>
#include <sddl.h>
#include <iostream>
#include <string>

#define BUFFER 1024
#define err(x, e) { cout << x << e << "\n"; goto Cleanup; }

using namespace std;

int main()
{
    PSECURITY_DESCRIPTOR securityDescriptor = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);

    PSID sidOwner = (PSID)LocalAlloc(LPTR, SECURITY_MAX_SID_SIZE);
    DWORD cbSidOwner = SECURITY_MAX_SID_SIZE;
    PSID sidWorld = (PSID)LocalAlloc(LPTR, SECURITY_MAX_SID_SIZE);;
    DWORD cbSidWorld = SECURITY_MAX_SID_SIZE;

    EXPLICIT_ACCESS explicitEntries[2];
    PACL newAcl = NULL;

    SECURITY_ATTRIBUTES securityAttributes;

    HKEY hKey = NULL;
    DWORD disposition = NULL;
    LONG ret = NULL;

    if (securityDescriptor == NULL)
        err("securityDescriptor NULL ", GetLastError());
    if (!InitializeSecurityDescriptor(securityDescriptor, SECURITY_DESCRIPTOR_REVISION))
        err("Failed at InitializeSecurityDescriptor(): ", GetLastError());
   
    if (!CreateWellKnownSid(WinCreatorOwnerSid, NULL, sidOwner, &cbSidOwner))
        err("Failed at CreateWellKnownSid(): ", GetLastError());
    if (sidOwner == NULL)
        err("sidOwner NULL ", GetLastError());
    
    if (!CreateWellKnownSid(WinWorldSid, NULL, sidWorld, &cbSidWorld))
        err("Failed at CreateWellKnownSid(): ", GetLastError());
    if (sidWorld == NULL)
        err("sidWorld NULL ", GetLastError());

    ZeroMemory(&explicitEntries, 2*sizeof(EXPLICIT_ACCESS));

    explicitEntries[0].grfAccessPermissions = KEY_READ;
    explicitEntries[0].grfAccessMode = SET_ACCESS;
    explicitEntries[0].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    explicitEntries[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    explicitEntries[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    explicitEntries[0].Trustee.ptstrName = (LPTSTR)sidWorld;

    explicitEntries[1].grfAccessPermissions = KEY_ALL_ACCESS;
    explicitEntries[1].grfAccessMode = SET_ACCESS;
    explicitEntries[1].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    explicitEntries[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    explicitEntries[1].Trustee.TrusteeType = TRUSTEE_IS_USER;
    explicitEntries[1].Trustee.ptstrName = (LPTSTR) sidOwner;

    if (SetEntriesInAcl(2, explicitEntries, NULL, &newAcl) != 0)
        err("Failed at SetEntriesInAcl(): ", GetLastError());

    if (SetSecurityDescriptorDacl(securityDescriptor, TRUE, newAcl, FALSE) == FALSE)
        err("Failed at SetSecurityDescriptorDacl(): ", GetLastError());

    securityAttributes = { sizeof(SECURITY_ATTRIBUTES), securityDescriptor, FALSE };

    ret = RegCreateKeyEx(
        HKEY_LOCAL_MACHINE, "SOFTWARE\\_TEMA5_", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &securityAttributes, &hKey, &disposition
    );

    if(ret != 0)
        err("Failed at RegCreateKeyEx(): ",  ret);

    Cleanup:
    if (sidOwner) LocalFree(sidOwner);
    if (sidWorld) LocalFree(sidWorld);
    if (newAcl) LocalFree(newAcl);
    if (securityDescriptor) LocalFree(securityDescriptor);
    if (hKey) RegCloseKey(hKey);

    return 0;
}
