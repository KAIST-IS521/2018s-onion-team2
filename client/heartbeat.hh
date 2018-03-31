
#ifndef __HEARTBEAT__
#define __HEARTBEAT__
#include "timestamp.hh"
#include "parser.hh"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#define HB_PORT 60750
#define HB_SERVER_ADDR inet_addr("127.0.0.1")

using namespace parser;

class heartbeat{
private:
  char* OneTimeKey;
  time_t timestamp;
public:
  heartbeat(char* _OneTimeKey,time_t timestamp);
  char* getOneTimeKey();
  time_t getTimestamp();
  bool setOneTimeKey(char* _OneTimeKey);
  bool setTimestamp(time_t _timestamp);
};

// hbd = heartbeat daemon
namespace hbd{
  char* recvHeartbeat();
  void heartbeatListener();
  bool sendHeartbeat(char* send_source, int send_size);
}
#endif
