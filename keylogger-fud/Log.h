#ifndef LOG_H
#define	LOG_H
#include <cstring>
#include <iostream>
#include <cstdio>
#include "TimeLog.h"
#include "Config.h"
#include <fstream>
#include "newWinApi.h"
using namespace std;

class Log {
public:
    Log();
    bool createNewLog(string fileName);
    bool addNewLog(string fileName, string title, string character);
    bool addLog(string fileName, string character);
    bool fileExist(string fileName);
    void prepareSendLog();
private:
    bool firstRun;
    TimeLog *time;
    Config *config;
    newWinApi *newWinApix;

};




#endif	/* LOG_H */

