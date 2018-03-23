#ifndef __parser__
#define __parser__
#define BYTE unsigned char

namespace parser{
  bool streamParser(BYTE* stream);
  message* message㎩rser(BYTE* stream);
  node* list㎩rser(BYTE* stream);
  heartbeat* hbParser(BYTE* stream);
  encMessage* encMessageParser(BYTE* stream);

  BYTE* packEncMessage(encMessage* src);
  BYTE* packMessage(message* src);
  BYTE* packNode(node* src);
  BYTE* packHeartBeat(heartbeat* src);
}

#endif
