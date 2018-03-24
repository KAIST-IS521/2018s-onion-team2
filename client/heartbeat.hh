
#ifndef __HEARTBEAT__
#define __HEARTBEAT__

class heartbeat{
private:
  char* OneTimeKey;
  time_t timestamp;
public:
  heartbeat(char* stream);
  heartbeat(char* _OneTimeKey,time_t timestamp);
  char* getOneTimeKey();
  time_t getTimestamp();
  bool setOntTimeKey(char* _OneTimeKey);
  bool setTimestamp(time_t _timestamp);
}

// hbd = heartbeat daemon
using namespace hbd{
  char* recvHeartbeat();
  void heartbeatListener();
  bool sendHeartbeat(char* send_source);
}
#endif
