#ifndef MAIL_H
#define	MAIL_H
#include "Message.h"
#include "SMTPTransoprt.h"
#include <cstring>
#include <cstdio>
#include <iostream> //TODO! Do usuniecia (cout)
#include <sstream>
#include "MailAccont.h"
#include "Config.h"
using namespace std;

class Mail {
public:
    Mail(string host, string login, string password, int port); 
    Mail(string host, string login, string password, string port); 
    Mail(MailAccont mailAccont);
    bool sendMail(string subject, string content, bool isAttachment = false, string attachmentPath = "");
private:
    SMTPTransport smtp;
    Config *config;

};

#endif	/* MAIL_H */

