#ifndef __transmission__
#define __transmission__
#define MESSAGE_PORT 56827
#define MAX_LEN 512
#define MAX_QUEUE 5
#include "userInfo.hh"
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

struct arg_struct {
  int recvFd;
  userInfo user;
};

// tmd = TransMission Daemon
namespace tmd{
  void* tmdReciver(void* args);
  void* tmdReciverMain(void* args);
  list<node*> tmdPathSelecter();
  // char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
  // bool tmdSender(string IP,char* scheme);
}

#endif

