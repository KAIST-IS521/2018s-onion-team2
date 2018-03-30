#ifndef __parser__
#define __parser__
#include <iostream>
#include <cstring>
#include "timestamp.hh"
#include "nodelist.hh"

namespace parser{
  message* messageParser(char* stream);
  node* listParser(char* stream);
  char getListmode(char* stream);
  heartbeat* hbParser(char* stream);
  encMessage* encMessageParser(char* stream);

  char* packEncMessage(encMessage* src);
  char* packMessage(message* src);
  char* packNode(node* src,char* mode);
  char* packHeartBeat(heartbeat* src);
}

#endif
