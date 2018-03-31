#ifndef __transmission__
#define __transmission__
#define HB_PORT 60750
#define MESSAGE_PORT 56827
#define MAX_LEN 512
#define MAX_QUEUE 5
#include "userInfo.hh"
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

struct arg_main {
  int protocol;
  int port;
  int type;
  void*(*func)(void*);
  userInfo user;
};

struct arg_receiver {
  int recvFd;
  userInfo user;
  string IP;
};

// tmd = TransMission Daemon
namespace tmd{
  void* tmdReciver(void* args);
  void* tmdReciverMain(void* args);
  void msg_args(userInfo user, struct arg_main* arguments);
  list<node*> tmdPathSelecter();
  // char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
  // bool tmdSender(string IP,char* scheme);
}

#endif

