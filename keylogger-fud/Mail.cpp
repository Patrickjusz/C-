#include "Mail.h"

Mail::Mail(string host, string login, string password, int port) {
    config = new Config();
    this->smtp.setHostAddress(host);
    this->smtp.setSenderAddress(login);
    this->smtp.setSenderPassword(password);
    this->smtp.setPort(port);
}

Mail::Mail(string host, string login, string password, string port) {
    config = new Config();
    this->smtp.setHostAddress(host);
    this->smtp.setSenderAddress(login);
    this->smtp.setSenderPassword(password);
    int portInt;
    stringstream(port) >> portInt;
    this->smtp.setPort(portInt);
}

Mail::Mail(MailAccont mailAccont) {
    config = new Config();
    this->smtp.setHostAddress(mailAccont.GetHost());
    this->smtp.setSenderAddress(mailAccont.GetLogin());
    this->smtp.setSenderPassword(mailAccont.GetPassword());
    int portInt;
    stringstream(mailAccont.GetPort()) >> portInt;
    this->smtp.setPort(portInt);
}

bool Mail::sendMail(string subject, string content, bool isAttachment, string attachmentPath) {
    Message message;
    message.addRecipient(config->GetToMail());
    config->GetToMail();
    message.setSubject(subject);
    message.setContents(content);

    if (isAttachment) {
        if (FILE * file = fopen(attachmentPath.c_str(), "r")) {
            fclose(file);
            //file exists
            message.addAttachment(attachmentPath);
        } else {
            //file not exists 
            //TODO TRY
        }
    }

    if (this->smtp.send(message)) {
        return true; //send OK
    } else {
        return false; //send FAIL
    }
}
