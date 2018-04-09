#ifndef __PARSER__
#define __PARSER__
#include "util.hh"
#include "timestamp.hh"
#include "transmission.hh" 
#include <iostream>
#include <string>
#include <cstring>

namespace parser{
  void messageParser(char* stream, message* dest);
  node* nodeParser(char* stream);
  encMessage* encMessageParser(char* stream);

  int packEncMessage(char* stream,encMessage* src);
  int packMessage(char* stream, message* src,string IP);
  int packNode(char* stream,node* src,char mode);

  int getMessagePackLen(message* src);
  int getEncMessagePackLen(encMessage* src);
}

#endif
