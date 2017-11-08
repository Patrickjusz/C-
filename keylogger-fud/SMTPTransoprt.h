#ifndef SMTPTRANSPORT_H
#define SMTPTRANSPORT_H

#include "message.h"

class SMTPTransport
{
public:
    //enum Encryption {Lack, SSL, TLS};

    SMTPTransport(const std::string & senderAddress = std::string(),
                  const std::string & senderPassword = std::string(),
                  const std::string & hostAddress = std::string(),
                  unsigned port = 465/*, Encryption encryption = SSL*/);

    //Encryption  getEncryption() const { return encryption; }
    std::string getHostAddress() const { return hostAddress; }
    std::string getLastError() const { return lastError; }
    unsigned    getPort() const { return port; }
    std::string getSenderAddress() const { return senderAddress; }
    std::string getSenderPassword() const { return senderPassword; }
    bool        isConfigured() const;
    bool        send(Message & message);
    //void        setEncryption(Encryption newEncryption) { encryption = newEncryption; }
    void        setHostAddress(const std::string & newHostAddress) { hostAddress = newHostAddress; }
    void        setPort(unsigned newPort) { port = newPort; }
    bool        setSenderAddress(const std::string & e_mailAddress);
    void        setSenderPassword(const std::string & password) { senderPassword = password; }

private:
    std::string getFileName(const std::string & file) const { return file.substr(file.rfind('\\')+1); }
    std::string getMIMEType(const std::string & file) const;
    std::string readFile(const std::string & filePath) const;
    std::string toBase64(const std::string & stringToEncode) const;

    //Encryption  encryption;
    std::string hostAddress;
    mutable std::string lastError;
    unsigned    port;
    std::string senderAddress;
    std::string senderPassword;

};

#endif // SMTPTRANSPORT_H
