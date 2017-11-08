#include "Xor.h"

Xor::Xor(string key) {
    key = key;
    this->key = key;
}

Xor::Xor() {
}

//string Xor::encryptDecrypt(string text) {
//    string key = this->key;
//    bool isEncrypted = true;
//    if (isEncrypted) {
//        text = this->hexToString(text);
//    }
//
//    string output = text;
//
//    for (int i = 0; i < text.size(); i++)
//        output[i] = text[i] ^ key[i % key.length()];
//
//    if (isEncrypted) {
//        return output;
//    } else {
//
//        return this->stringToHex(output);
//    }
//}

string Xor::encryptDecryptTest(string text, bool isEncrypted = true) {
    //true odszyfrowuje zaszyfrowane dane
    string key = this->key;
    //isEncrypted = false;
    if (isEncrypted) {
        text = this->hexToString(text);
    }

    string output = text;

    for (int i = 0; i < text.size(); i++)
        output[i] = text[i] ^ key[i % key.length()];

    if (isEncrypted) {
        return output;
    } else {

        return this->stringToHex(output);
    }
}

string Xor::stringToHex(const std::string& input) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i) {

        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

string Xor::hexToString(const std::string& input) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2) {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}


LPCTSTR Xor::encryptStringToLPCTSTR(string str) {
    //rzutuje string i koduje XOR i zwraca LPCTSTR (pod WinApi)
    string encrypted = this->encryptDecryptTest(str, true);
    LPTSTR lptstrConvertTmp = new TCHAR[encrypted.size() + 1];
    strcpy(lptstrConvertTmp, encrypted.c_str());
    return lptstrConvertTmp;
}