#ifndef __PARSER__
#define __PARSER__
#include "util.hh"
#include "timestamp.hh"
#include "transmission.hh" 
#include <iostream>
#include <string>
#include <cstring>

class heartbeat;

namespace parser{
  void messageParser(char* stream, message* dest);
  node* nodeParser(char* stream);
  char getListmode(char* stream);
  heartbeat* hbParser(char* stream);
  encMessage* encMessageParser(char* stream);

  int packEncMessage(char* stream,encMessage* src);
  int packMessage(char* stream, message* src,string IP);
  int packNode(char* stream,node* src,char mode);
  int packHeartBeat(char* stream, char* OTK);
  void packListUpdate(char mode, struct tmd::arg_data* args);

  int getMessagePackLen(message* src);
  int getEncMessagePackLen(encMessage* src);
  int getNodePackLen(node* src);
  int getHeartBeatPackLen(heartbeat* src);
}

#endif
