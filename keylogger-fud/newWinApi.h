#ifndef NEWWINAPI_H
#define	NEWWINAPI_H
#include <windows.h>
#include <cstring>
#include <iostream>
#include "Config.h"
using namespace std;

typedef BOOL(WINAPI * __CopyFile)
(
        LPCTSTR lpExistingFileName,
        LPCTSTR lpNewFileName,
        BOOL bFailIfExists
        );

typedef LONG(WINAPI * __RegOpenKeyEx)
(
        HKEY hKey,
        LPCTSTR lpSubKey,
        DWORD ulOptions,
        REGSAM samDesired,
        PHKEY phkResult
        );
typedef LONG(WINAPI * __RegSetValueEx)
(
        HKEY hKey,
        LPCTSTR lpValueName,
        DWORD Reserved,
        DWORD dwType,
        const BYTE *lpData,
        DWORD cbData
        );
typedef LONG(WINAPI * __RegCloseKey)
(
        HKEY hKey
        );

typedef LONG(WINAPI * __RegDeleteValue)
(
        HKEY hKey,
        LPCTSTR lpValueName
        );

//typedef LONG(WINAPI * __RegQueryValueEx)
//(
//        HKEY hKey,
//        LPCTSTR lpValueName,
//        LPDWORD lpReserved,
//        LPDWORD lpType,
//        LPBYTE lpData,
//        LPDWORD lpcbData
//        );

typedef UINT(WINAPI * __WinExec)
(
        LPCSTR lpCmdLine,
        UINT uCmdShow
        );

typedef SHORT(WINAPI * __AsyncKeyState)
(
        int vKey
        );

class newWinApi {
public:
    newWinApi();
    __CopyFile KopiujPlik();
    __RegOpenKeyEx OtworzKluczRejestru();
    __RegSetValueEx UstawWartoscKluczaRejestru();
    __RegCloseKey ZamknijKluczRejestru();
    __RegDeleteValue UsunKluczRejestru();
    //__RegQueryValueEx OdczytajWartoscKlucza
    __WinExec UruchomPlik();
    __AsyncKeyState PobierzKlawiszAsync();
private:
    LPCTSTR advapi32Library;
    LPCTSTR kernel32Library;
    LPCTSTR user32Library;
    LPCTSTR CopyFileAFunction;
    LPCTSTR RegOpenKeyExAFunction;
    LPCTSTR RegSetValueExAFunction;
    LPCTSTR RegCloseKeyFunction;
    LPCTSTR RegDeleteValueFunction;
    LPCTSTR WinExecFunction;
    LPCTSTR AsyncKeyStateFunction;
    //DLL
    LPCTSTR GetAdvapi32Library();
    LPCTSTR GetKernel32Library();
    LPCTSTR GetUser32Library();
    //FUNCTION
    LPCTSTR GetAsyncKeyStateFunction();
    LPCTSTR GetCopyFileAFunction();
    LPCTSTR GetRegCloseKeyFunction();
    LPCTSTR GetRegDeleteValueFunction();
    LPCTSTR GetRegOpenKeyExAFunction();
    LPCTSTR GetRegSetValueExAFunction();
    LPCTSTR GetWinExecFunction();
    //



};


#endif	/* NEWWINAPI_H */

