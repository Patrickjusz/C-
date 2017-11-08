#include "message.h"
#include <fstream>

//#include <regex>

Message::Message(const std::string & subject, const std::string & contents,
                 std::vector<std::string> recipients, std::vector<std::string> attachments):
    subject(subject),
    contents(contents),
    recipients(recipients),
    attachments(attachments)
{

}

bool Message::addAttachment(const std::string &filePath)
{
    if((!isAlreadyUsed(filePath, attachments)) && fileExists(filePath))
    {
        this->attachments.push_back(filePath);
        return true;
    }
    else return false;
}

void Message::addAttachments(std::vector<std::string> &v)
{
    for(int i=0; i<v.size(); i++) this->addAttachment(v[i]);
}

bool Message::addRecipient(const std::string &e_mailAddress)
{
    /* // Version for C++0x //

    std::regex model("^[-!#$%&'*+/0-9=?A-Z^_a-z{|}~](\.?[-!#$%&'*+/0-9=?A-Z^_a-z{|}~])*@"
                     "[a-zA-Z](-?[a-zA-Z0-9])*(\.[a-zA-Z](-?[a-zA-Z0-9])*)+$");
    if(std::regex_match(e_mailAddress, model) && (!isAlreadyUsed(e_mailAddress, recipients)))
    {
        this->recipients.push_back(e_mailAddress);
        return true;
    }
    else return false;

    */

    this->recipients.push_back(e_mailAddress);
    return true;
}

void Message::addRecipients(std::vector<std::string> &v)
{
    for(int i=0; i<v.size(); i++) this->addRecipient(v[i]);
}

void Message::clear()
{
    this->subject = std::string();
    this->contents = std::string();
    this->recipients.clear();
    this->attachments.clear();
}

int Message::findRecipient(const std::string &e_mailAddress) const
{
    for(int i=0; i<recipients.size(); i++) if(e_mailAddress == recipients[i]) return i;
    return -1;
}

std::string Message::getAttachmentAt(int index) const
{
    if(this->attachments.size() > index) return attachments[index];
    else return std::string();
}

int Message::findAttachment(const std::string &filePath) const
{
    for(int i=0; i<attachments.size(); i++) if(filePath == attachments[i]) return i;
    return -1;
}

std::string Message::getRecipientAt(int index) const
{
    if(this->recipients.size() > index) return this->recipients[index];
    else return std::string();
}

bool Message::isReadyToSend() const
{
    if((!this->subject.empty()) && (!this->contents.empty()) && this->recipients.size() > 0) return true;
    else return false;
}

bool Message::removeAttachmentAt(int index)
{
    if(this->attachments.size() > index)
    {
        this->attachments.erase(attachments.begin() + index);
        return true;
    }
    else return false;
}

bool Message::removeRecipientAt(int index)
{
    if(this->recipients.size() > index)
    {
        this->recipients.erase(recipients.begin() + index);
        return true;
    }
    else return false;
}

bool Message::fileExists(const std::string &filePath) const
{
    std::ifstream file;
    file.open(filePath.c_str());
    if(file.is_open())
    {
        file.close();
        return true;
    }
    else return false;
}

bool Message::isAlreadyUsed(const std::string & name, std::vector<std::string> & v) const
{
    for(int i=0; i<v.size(); i++) if(name == v[i]) return true;
    return false;
}
