#ifndef STRINGCRYPTER_H
#define STRINGCRYPTER_H
#include <iostream>
#include <cstring>
using namespace std;
class StringCrypter
{
public:
    StringCrypter(string key);
    string encryptDecrypt(string text, bool encrypted);

private:
    string strToHex(const string& text);
    string hexToStr(const string& text);
    string xorKey;
};

#endif // STRINGCRYPTER_H
