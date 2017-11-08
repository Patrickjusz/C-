#include "Window.h"

Window::Window() {
    //    this->lastWindowName = this->getWindowName();
    this->lastWindowName = " ";
}

string Window::getWindowName() {
    HWND windowHandle = GetForegroundWindow();
    // char buffor[65536];

    char *buffor;
    string windowName;
    int windowNameLenght = GetWindowTextLength(windowHandle);
    buffor = (char*) malloc(windowNameLenght + 1);

    GetWindowText(windowHandle, buffor, windowNameLenght + 1);
    windowName = buffor;
    free(buffor);
    return windowName.c_str();
}

bool Window::isNewWindow() {
    string windowName = this->getWindowName();
    if (windowName == this->lastWindowName)
        return false;
    else
        this->lastWindowName = windowName;
    return true;
}

string Window::getLastWindowName() {
    return this->lastWindowName;
}