#include "MailAccont.h"

MailAccont::MailAccont() {
    //encrypted host, login, password, port
    Config *config = new Config();
    this->host = config->GetHost();
    this->login = config->GetLogin();
    this->password = config->GetPassword();
    this->port = config->GetPort();
}

MailAccont::MailAccont(string host, string login, string password, string port) {
    this->host = host;
    this->login = login;
    this->password = password;
    this->port = port;
}

MailAccont MailAccont::getPlainAccount() {
    string host = this->host;
    string login = this->login;
    string password = this->password;
    string port = this->port;
    MailAccont *ma = new MailAccont(host, login, password, port);
    cout << host << login << password << port << endl;
    return *ma;
}

string MailAccont::GetHost() {
    return this->host;
}

string MailAccont::GetLogin() {
    return this->login;
}

string MailAccont::GetPassword() {
    return this->password;
}

string MailAccont::GetPort() {
    return this->port;
}
