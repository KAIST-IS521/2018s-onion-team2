#ifndef __gpg__
#define __gpg__
#include <iostream>
#include <cstdio>
#include <string>
#include <regex>
using namespace std;

namespace gpg{
  char* encBytestream(char* src, string* PubKeyID, int length);
  char* decBytestream(char* src, string* passphase);
}

#endif
