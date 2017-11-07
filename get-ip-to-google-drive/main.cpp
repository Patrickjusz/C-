#include <winsock2.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
// ZMIEŃ FRAZE TWOJ_HOST na twój hosting z skryptem ip.php
string getNowTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char str[158];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(str, "%02d-%02d-%d | %02d:%02d", timeinfo->tm_mday, (timeinfo->tm_mon + 1), (1900 + timeinfo->tm_year), timeinfo->tm_hour, timeinfo->tm_min);
    return str;
}

int main ()
{
    cout << "Oczekuje 10s zanim pobiore IP..." << endl;
    Sleep(10000);
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        cout << "BLAD.\n";
        //system("pause");
        return 1;
    }

    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname("www.TWOJ_HOST.pl");

    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    cout << "Pobieram adres IP...\n";
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0)
    {
        cout << "Brak internetu...";
        //system("pause");
        return 1;
    }
    cout << "Polaczony.\n";

    send(Socket,"GET /ip.php?token=04162ddea246826e7a72497e23c16918 HTTP/1.1\r\nHost: www.haker.hekko24.pl\r\nConnection: close\r\n\r\n", strlen("GET /ip.php?token=04162ddea246826e7a72497e23c16918 HTTP/1.1\r\nHost: www.TWOJ_HOST.pl\r\nConnection: close\r\n\r\n"),0);
    char buffer[10000];
    int nDataLength;

    while ((nDataLength = recv(Socket,buffer,10000,0)) > 0)
    {
        int i = 0;
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
        {
            i += 1;
        }
    }

    closesocket(Socket);
    WSACleanup();


    std::string kodHtml = buffer;
    std::string tag1 ("<iptag>");
    std::string tag2 ="</iptag>";
    std::size_t found1 = kodHtml.find(tag1);
    std::size_t found2 = kodHtml.find(tag2);
    string adresIP = kodHtml.substr(found1+7, found2-found1-7);
    cout << adresIP << endl;


    FILE * plikSciezki;
    plikSciezki = fopen ("sciezka.txt","r");
    char sciezka[1024];
    if (plikSciezki!=NULL)
    {
        fgets (sciezka, 1024, plikSciezki);
        fclose (plikSciezki);

        //ZAPISUJE PLIK IP.txt
        FILE * plikIP;
        plikIP = fopen (sciezka,"w");
        if (plikIP!=NULL)
        {
            string log = adresIP+" | "+getNowTime();
            cout << log;
            fputs (log.c_str(),plikIP);
            fclose (plikIP);
        }
    }

    return 0;
}
