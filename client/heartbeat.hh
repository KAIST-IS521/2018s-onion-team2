#ifndef __HEARTBEAT__
#define __HEARTBEAT__
#include "timestamp.hh"
#include "util.hh"
#include "userInfo.hh"
#include "transmission.hh"

#define HB_LEN 9
#define SERVER_ADDR "127.0.0.1"

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
  void heartbeat_args(userInfo user, struct arg_main* arguments);
}
#endif
