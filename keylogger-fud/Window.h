/* 
 * File:   Window.h
 * Author: Patryk
 *
 * Created on 21 kwiecień 2015, 23:23
 */

#ifndef WINDOW_H
#define	WINDOW_H
#include <cstring>
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

class Window {
public:
    Window();
    bool isNewWindow();
    string getLastWindowName();

private:
    string lastWindowName;
    string getWindowName();

};

#endif	/* WINDOW_H */

