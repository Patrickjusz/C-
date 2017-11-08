/* 
 * File:   TimeLog.h
 * Author: Patryk
 *
 * Created on 22 kwiecień 2015, 00:23
 */

#ifndef TIMELOG_H
#define	TIMELOG_H
#include <cstring>
#include <time.h>
#include <iostream>
#include <cstdio>
#include "Config.h"

using namespace std;

class TimeLog {
public:
    TimeLog();
    int getTimeMs();
    string loadFileTime();
    bool saveFileTime();
    bool compareTime();
    string getNowTime();
private:
    Config *config;

};

#endif	/* TIMELOG_H */

