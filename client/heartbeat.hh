
#ifndef __HEARTBEAT__
#define __HEARTBEAT__

class heartbeat{
private:
  BYTE* OneTimeKey;
  long timestamp;
public:
  heartbeat();
  BYTE* getOneTimeKey(BYTE* _OneTimeKey,long timestamp);
  long getTimestamp();
  bool setOntTimeKey(BYTE* _OneTimeKey);
  bool setTimestamp(long _timestamp);
}

// hbd = heartbeat daemon
using namespace hbd{
  BYTE* recvHeartbeat();
  void heartbeatListener();
  bool sendHeartbeat(BYTE* send_source);
}
#endif
