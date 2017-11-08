#ifndef XOR_H
#define	XOR_H
#include <cstring>
#include <cstdio>
#include <iostream> //TODO! Do usuniecia (cout)
#include <algorithm>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <windows.h>
using namespace std;

class Xor {
public:
    Xor();
    Xor(string key);
//    string encryptDecrypt(string text);
    string encryptDecryptTest(string text, bool isEncrypted);
    LPCTSTR encryptStringToLPCTSTR(string str);
private:
    string key;
    string hexToString(const std::string& input);
    string stringToHex(const std::string& input);




};

#endif	/* XOR_H */

