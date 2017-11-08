#include "SMTPTransoprt.h"
#include <fstream>
//#include <regex>
#include <sstream>
#include <streambuf>
#include <WinSock2.h>

SMTPTransport::SMTPTransport(const std::string & senderAddress, const std::string & senderPassword,
                             const std::string & hostAddress, unsigned port/*, Encryption encryption*/):
    senderPassword(senderPassword),
    hostAddress(hostAddress),
    port(port)/*,
    encryption(encryption)*/
{
    setSenderAddress(senderAddress);
}

inline bool SMTPTransport::isConfigured() const
{
    return (!(this->senderAddress.empty()) && !(this->senderPassword.empty()) && !(this->hostAddress.empty()));
}

bool SMTPTransport::send(Message &message)
{
    if(!message.isReadyToSend())
    {
        this->lastError = "Message is not ready to send";
        return false;
    }
    if(!(this->isConfigured()))
    {
        this->lastError = "SMTPTransport is not configured";
        return false;
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    LPHOSTENT hostEntry = gethostbyname(this->hostAddress.c_str());
    if(hostEntry == 0)
    {
        this->lastError = "gethostbyname returns a null pointer";
        WSACleanup();
        return false;
    }
    SOCKADDR_IN saddr;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    const unsigned sizeBuffer = 1024;
    char buffer[sizeBuffer];
    std::string tempString, tempString2;

    saddr.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(this->port);

    if(connect(sock, (sockaddr*)&saddr, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        this->lastError = "SOCKET_ERROR";
        WSACleanup();
        return false;
    }

    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    tempString = "EHLO " + this->hostAddress + "\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    ::send(sock, "AUTH LOGIN\r\n", 12, 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    tempString = this->toBase64(this->senderAddress) + "\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    tempString = this->toBase64(this->senderPassword) + "\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    tempString = "MAIL FROM: <" + this->senderAddress + ">\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    for(int i=0; i<message.getRecipientCount(); i++)
    {
        tempString = "RCPT TO: <" + message.getRecipientAt(i) + ">\r\n";
        tempString2 += (message.getRecipientAt(i) + ", ");
        ::send(sock, tempString.c_str(), tempString.size(), 0);
        recv(sock, buffer, sizeBuffer - 1, 0);
        if(buffer[0] == '5' || buffer[0] == '4')
        {
            this->lastError = buffer;
            closesocket(sock);
            WSACleanup();
            return false;
        }
    }

    ::send(sock, "DATA\r\n", 6, 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    ::send(sock, "MIME-Version: 1.0\r\n", 19, 0);

    tempString = "Subject: =?Windows-1250?B?" + this->toBase64(message.getSubject()) + "?=\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);

    tempString = "From: " + this->senderAddress + "\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);

    tempString = "To: " + tempString2 + "\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);

    if(message.getAttachmentCount() > 0)
    {
        ::send(sock, "Content-Type: multipart/mixed; boundary=00newline9\r\n\r\n", 54, 0);
        ::send(sock, "--00newline9\r\n", 14, 0);
    }

    ::send(sock, "Content-Type: text/plain; charset=Windows-1250\r\n", 48, 0);
    ::send(sock, "Content-Transfer-Encoding: base64\r\n\r\n", 37, 0);

    tempString = this->toBase64(message.getContents()) + "\r\n\r\n";
    ::send(sock, tempString.c_str(), tempString.size(), 0);

    if(message.getAttachmentCount() > 0)
    {
        for(int i=0; i<message.getAttachmentCount(); i++)
        {
            ::send(sock, "--00newline9\r\n", 14, 0);

            tempString = "Content-Type: " + this->getMIMEType(message.getAttachmentAt(i)) +
                         "; name=\"" + this->getFileName(message.getAttachmentAt(i)) + "\"\r\n";
            ::send(sock, tempString.c_str(), tempString.size(), 0);

            tempString = "Content-Disposition: attachment; filename=\"" + getFileName(message.getAttachmentAt(i)) + "\"\r\n";
            ::send(sock, tempString.c_str(), tempString.size(), 0);

            ::send(sock, "Content-Transfer-Encoding: base64\r\n\r\n", 37, 0);

            tempString = this->toBase64(this->readFile(message.getAttachmentAt(i))) + "\r\n";
            ::send(sock, tempString.c_str(), tempString.size(), 0);
        }

        ::send(sock, "--00newline9--\r\n", 16, 0);
    }

    ::send(sock, ".\r\n", 3, 0);
    recv(sock, buffer, sizeBuffer - 1, 0);
    if(buffer[0] == '5' || buffer[0] == '4')
    {
        this->lastError = buffer;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    ::send(sock, "QUIT\r\n", 6, 0);
    recv(sock, buffer, sizeBuffer - 1, 0);

    closesocket(sock);
    WSACleanup();
    return true;
}

bool SMTPTransport::setSenderAddress(const std::string &e_mailAddress)
{
    /* // Version for C++0x //

    std::regex model("^[-!#$%&'*+/0-9=?A-Z^_a-z{|}~](\.?[-!#$%&'*+/0-9=?A-Z^_a-z{|}~])*@"
                     "[a-zA-Z](-?[a-zA-Z0-9])*(\.[a-zA-Z](-?[a-zA-Z0-9])*)+$");
    if(std::regex_match(e_mailAddress, model))
    {
        this->senderAddress = e_mailAddress;
        return true;
    }
    else return false;

    */

    this->senderAddress = e_mailAddress;
    return true;
}

std::string SMTPTransport::getMIMEType(const std::string &file) const
{
    std::string enlargement = file.substr(file.rfind('.')+1);

    /*  The most popular types of files */
    if(enlargement=="zip")  return "application/zip";
    if(enlargement=="rar")  return "application/rar";
    if(enlargement=="mp3")  return "audio/mpeg";
    if(enlargement=="pdf")  return "application/pdf";
    if(enlargement=="html") return "text/html";
    if(enlargement=="htm")  return "text/html";
    if(enlargement=="png")  return "image/png";
    if(enlargement=="gif")  return "image/gif";
    if(enlargement=="bmp")  return "image/bmp";
    if(enlargement=="jpeg") return "image/jpeg";
    if(enlargement=="jpg")  return "image/jpeg";
    if(enlargement=="pps")  return "application/vnd.ms-powerpoint";
    if(enlargement=="ppt")  return "application/vnd.ms-powerpoint";
    if(enlargement=="pptx") return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    if(enlargement=="xls")  return "application/vnd.ms-excel";
    if(enlargement=="xlsx") return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    if(enlargement=="txt")  return "text/plain";
    if(enlargement=="doc")  return "application/msword";
    if(enlargement=="docx") return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    if(enlargement=="avi")  return "video/x-msvideo";
    if(enlargement=="mov")  return "video/quicktime";
    if(enlargement=="wmv")  return "video/x-ms-wmv";
    if(enlargement=="mpeg") return "video/mpeg";
    if(enlargement=="mpg")  return "video/mpeg";
    if(enlargement=="wma")  return "audio/x-ms-wma";
    /*  Graphic files */
    if(enlargement=="jpe")  return "image/jpeg";
    if(enlargement=="ico")  return "image/x-icon";
    if(enlargement=="psd")  return "application/photoshop";
    if(enlargement=="tif")  return "image/tiff";
    if(enlargement=="tiff") return "image/tiff";
    if(enlargement=="xpm")  return "image/x-xpixmap";
    if(enlargement=="svg")  return "image/svg+xml";
    if(enlargement=="swf")  return "application/x-shockwave-flash";
    if(enlargement=="eps")  return "application/postscript";
    /*  Audio files */
    if(enlargement=="ra")   return "audio/x-realaudio";
    if(enlargement=="rm")   return "audio/x-pn-realaudio";
    if(enlargement=="ram")  return "audio/x-pn-realaudio";
    if(enlargement=="wav")  return "audio/x-wav";
    if(enlargement=="mid")  return "audio/midi";
    if(enlargement=="midi") return "audio/midi";
    if(enlargement=="aif")  return "audio/x-aiff";
    if(enlargement=="aiff") return "audio/x-aiff";
    if(enlargement=="aifc") return "audio/x-aiff";
    if(enlargement=="mp2")  return "audio/mpeg";
    /*  Video files */
    if(enlargement=="mp4")  return "video/mp4";
    if(enlargement=="mpe")  return "video/mpeg";
    if(enlargement=="ogv")  return "video/ogg";
    if(enlargement=="qt")   return "video/quicktime";
    if(enlargement=="asf")  return "video/x-ms-asf";
    /*  Text documents */
    if(enlargement=="odt")  return "application/vnd.oasis.opendocument.text";
    if(enlargement=="ott")  return "application/vnd.oasis.opendocument.text-template";
    if(enlargement=="pages")return "application/x-iwork-pages-sffpages";
    if(enlargement=="rtf")  return "application/rtf";
    if(enlargement=="sxw")  return "application/vnd.sun.xml.writer";
    /*  Spreadsheets */
    if(enlargement=="csv")  return "text/csv";
    if(enlargement=="ods")  return "application/vnd.oasis.opendocument.spreadsheet";
    if(enlargement=="ots")  return "application/vnd.oasis.opendocument.spreadsheet-template";
    if(enlargement=="sxc")  return "application/vnd.sun.xml.calc";
    /*  Multimedia presentations */
    if(enlargement=="ppsx") return "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    if(enlargement=="odp")  return "application/vnd.oasis.opendocument.presentation";
    if(enlargement=="otp")  return "application/vnd.oasis.opendocument.presentation-template";
    if(enlargement=="sxi")  return "application/vnd.sun.xml.impress";
    /*  Archives */
    if(enlargement=="tar")  return "application/x-tar";
    if(enlargement=="tgz")  return "application/x-gzip";
    /*  Other */
    if(enlargement=="xml")  return "text/xml";
    if(enlargement=="php")  return "application/x-httpd-php";
    if(enlargement=="cpp")  return "text/x-c++src";
    if(enlargement=="c")    return "text/x-csrc";
    if(enlargement=="js")   return "application/x-javascript";

    return "application/octet-stream";
}

std::string SMTPTransport::readFile(const std::string &filePath) const
{
    std::ifstream file(filePath.c_str(), std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string SMTPTransport::toBase64(const std::string &stringToEncode) const
{
    static const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

    std::string result;
    unsigned size = stringToEncode.size();
    int i=0, j=0, index=0;
    unsigned char charArrary3[3];
    unsigned char charArrary4[4];

    while(size--)
    {
        charArrary3[i++] = stringToEncode[index++];
        if(i == 3)
        {
            charArrary4[0] = (charArrary3[0] & 0xfc) >> 2;
            charArrary4[1] = ((charArrary3[0] & 0x03) << 4) + ((charArrary3[1] & 0xf0) >> 4);
            charArrary4[2] = ((charArrary3[1] & 0x0f) << 2) + ((charArrary3[2] & 0xc0) >> 6);
            charArrary4[3] = charArrary3[2] & 0x3f;

            for(i=0; i<4; i++) result += base64Chars[charArrary4[i]];
            i = 0;
        }
    }

    if(i)
    {
        for(j=i; j<3; j++) charArrary3[j] = '\0';
        charArrary4[0] = (charArrary3[0] & 0xfc) >> 2;
        charArrary4[1] = ((charArrary3[0] & 0x03) << 4) + ((charArrary3[1] & 0xf0) >> 4);
        charArrary4[2] = ((charArrary3[1] & 0x0f) << 2) + ((charArrary3[2] & 0xc0) >> 6);
        charArrary4[3] = charArrary3[2] & 0x3f;

        for(j=0; j<i+1; j++) result += base64Chars[charArrary4[j]];

        while(i++ < 3) result += '=';
    }

    return result;
}
