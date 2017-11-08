#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

class Message
{
public:
    Message(const std::string & subject = std::string(), const std::string & contents = std::string(),
            std::vector<std::string> recipients = std::vector<std::string>(),
            std::vector<std::string> attachments = std::vector<std::string>());

    bool        addAttachment(const std::string & filePath);
    void        addAttachments(std::vector<std::string> & v);
    bool        addRecipient(const std::string & e_mailAddress);
    void        addRecipients(std::vector<std::string> & v);
    void        clear();
    int         findAttachment(const std::string & filePath) const;
    int         findRecipient(const std::string & e_mailAddress) const;
    std::vector<std::string> getAllAttachments() const { return attachments; }
    std::vector<std::string> getAllRecipients() const { return recipients; }
    std::string getContents() const { return contents; }
    std::string getAttachmentAt(int index) const;
    std::string getRecipientAt(int index) const;
    int         getAttachmentCount() const { return attachments.size(); }
    int         getRecipientCount() const { return recipients.size(); }
    std::string getSubject() const { return subject; }
    bool        isReadyToSend() const;
    bool        removeAttachmentAt(int index);
    bool        removeRecipientAt(int index);
    void        removeAllAttachments() { attachments.clear(); }
    void        removeAllRecipients() { recipients.clear(); }
    void        setContents(const std::string & newContents) { contents = newContents; }
    void        setSubject(const std::string & newSubject) { subject = newSubject; }


private:
    bool        fileExists(const std::string & filePath) const;
    bool        isAlreadyUsed(const std::string & name,std::vector<std::string> & v) const;

    std::vector<std::string> attachments;
    std::string contents;
    std::vector<std::string> recipients;
    std::string subject;

};

#endif // MESSAGE_H
