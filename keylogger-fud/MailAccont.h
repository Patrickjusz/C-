#ifndef MAILACCONT_H
#define	MAILACCONT_H
#include <cstring>
#include <iostream> //TODO! Do usuniecia (cout)
#include "Config.h"

using namespace std;

class MailAccont {
public:
    MailAccont();
    MailAccont(string host, string login, string password, string port);
    MailAccont getPlainAccount();
    string GetHost();
    string GetLogin();
    string GetPassword();
    string GetPort();
private:
    string host;
    string login;
    string password;
    string port;
};

#endif	/* MAILACCONT_H */

