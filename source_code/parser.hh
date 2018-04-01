#ifndef __parser__
#define __parser__
#include <iostream>
#include <string>
#include <cstring>
#include "timestamp.hh"
#include "nodelist.hh"
#include "heartbeat.hh"
#include "message.hh"
#include "util.hh"

namespace parser{
  message* messageParser(char* stream);
  node* nodeParser(char* stream);
  char getListmode(char* stream);
  heartbeat* hbParser(char* stream);
  encMessage* encMessageParser(char* stream);

  int packEncMessage(char* stream,encMessage* src);
  int packMessage(char* stream,message* src,string IP);
  int packNode(char* stream,node* src,char mode);
  int packHeartBeat(char* stream,heartbeat* src);
  void packListUpdate(char mode, userInfo user, struct tmd::arg_data* args);

  int getMessagePackLen(message* src);
  int getEncMessagePackLen(encMessage* src);
  int getNodePackLen(node* src);
  int getHeartBeatPackLen(heartbeat* src);
}

#endif
