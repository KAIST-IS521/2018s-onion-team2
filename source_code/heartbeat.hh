#ifndef __HEARTBEAT__
#define __HEARTBEAT__
#include "transmission.hh"

class heartbeat{
private:
  char OneTimeKey[4];
public:
  heartbeat(char* data);
  char* getOneTimeKey();
  void setHeartBeat(char* data, char* response);
};

// hbd = heartbeat daemon
namespace hbd{
  void* recvHeartbeat(void* args);
  void heartbeat_args(struct tmd::arg_main* arguments);
}
#endif
