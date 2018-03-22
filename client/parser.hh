#ifndef __parser__
#define __parser__
#define BYTE unsigned char

namespace parser{
  bool streamParser(BYTE* stream);
  bool message㎩rser(BYTE* stream , message _message);
  bool list㎩rser(BYTE* stream, nodelist curNodeList);
  bool hbParser(BYTE* stream, heartbeat recvBeat);
  
  BYTE* packMessage(String GithubID, String IP, String PubKeyID);
  BYTE* packHeartBeat(BYTE* OTK, long Timestamp);

}

#endif
