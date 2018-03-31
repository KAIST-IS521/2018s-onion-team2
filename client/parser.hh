#ifndef __parser__
#define __parser__
#define LIST_UPDATE 66
#include "userInfo.hh"

namespace parser{
  bool streamParser(char* stream);
  message* messageParser(char* stream);
  node* listParser(char* stream);
  heartbeat* hbParser(char* stream);
  encMessage* encMessageParser(char* stream);

  char* packEncMessage(encMessage* src,string IP);
  char* packMessage(message* src);
  char* packNode(node* src);
  char* packHeartBeat(heartbeat* src);
  void packListUpdate(char* mode, userInfo user, char* protocol);
}

#endif
