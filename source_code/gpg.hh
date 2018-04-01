#ifndef __gpg__
#define __gpg__
#include <iostream>
#include <cstdio>
#include <string>
#include <regex>
using namespace std;

namespace gpg{
  char* encBytestream(char* src, string* PubKeyID);
  bool keyRefresh();
  char* decBytestream(char* src, string* passphrase);
  bool recvPubKey(string* PubKeyID);
}

#endif
