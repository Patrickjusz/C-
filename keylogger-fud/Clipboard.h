/* 
 * File:   Clipboard.h
 * Author: Patryk
 *
 * Created on 19 maj 2015, 11:06
 */

#ifndef CLIPBOARD_H
#define	CLIPBOARD_H
#include <cstring>
#include <iostream>
#include <windows.h>

using namespace std;

class Clipboard {
public:
    Clipboard();
    bool isNewClipboard();
    string getLastClipboard();
private:
    string lastClipboardName;

};

#endif	/* CLIPBOARD_H */

