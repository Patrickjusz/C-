#include "TimeLog.h"

TimeLog::TimeLog() {
    this->config = new Config();
}

int TimeLog::getTimeMs() {
    return time(NULL);
}

string TimeLog::loadFileTime() {
    FILE *file = fopen(this->config->GetTimeFileName().c_str(), "r");
    if (file) {
        char tmpBuffor[16]; //UNIX TIME (s) BUFFOR (10 digit [1/1/1970 - 22/04/2015])
        fgets(tmpBuffor, 16, file);
        fclose(file);
        return tmpBuffor;
    } else {
        return "0";
    }
}

bool TimeLog::saveFileTime() {
    FILE *file = fopen(this->config->GetTimeFileName().c_str(), "w");
    if (file) {
        fprintf(file, "%d", this->getTimeMs());
        fclose(file);
        return true;
    } else {
        return false;
    }
}

bool TimeLog::compareTime() {
    int minutyPlik = 0;
    string wPlikuTxt = this->loadFileTime();
    minutyPlik = atoi(wPlikuTxt.c_str());
    int roznica = this->getTimeMs();
    roznica = roznica - minutyPlik;
    if (roznica >= this->config->GetSendMailTime()) {
        roznica = 0;
        this->saveFileTime();
        return true;
    }
    return false;
}

string TimeLog::getNowTime() {
    time_t rawtime;
    struct tm * timeinfo;
    char str[158];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(str, "%02d-%02d-%d | %02d:%02d", timeinfo->tm_mday, (timeinfo->tm_mon + 1), (1900 + timeinfo->tm_year), timeinfo->tm_hour, timeinfo->tm_min);
    return str;
}

