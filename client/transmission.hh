#ifndef __transmission__
#define __transmission__
#include "util.hh"
#include "userInfo.hh"
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

// tmd = TransMission Daemon
namespace tmd{
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
    char buf[HB_LEN];
  };

  void* tmdReciver(void* args);
  void* tmdReciverMain(void* args);
  void msg_args(userInfo user, struct tmd::arg_main* arguments);
  list<node*> tmdPathSelecter();
  // char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
  // bool tmdSender(string IP,char* scheme);
}

#endif

