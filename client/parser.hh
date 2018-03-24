#ifndef __parser__
#define __parser__

namespace parser{
  bool streamParser(char* stream);
  message* message㎩rser(char* stream);
  node* list㎩rser(char* stream);
  heartbeat* hbParser(char* stream);
  encMessage* encMessageParser(char* stream);

  char* packEncMessage(encMessage* src,string IP);
  char* packMessage(message* src);
  char* packNode(node* src);
  char* packHeartBeat(heartbeat* src);
}

#endif
