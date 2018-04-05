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
  };

  struct arg_receiver {
    int recvFd;
    string IP;
    char buf[HB_LEN];
  };

  struct arg_data {
    char* data;
    int length;
    string IP;
  };

  void* tmdReceiver(void* args);
  void* tmdReceiverMain(void* args);
  void msg_args(struct tmd::arg_main* arguments);
  void data_args(string IP, char* data, struct tmd::arg_data* list_update_arguments);
  list<node*> tmdPathSelecter();
  void* tmdSender(void* args);
  // char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
}

#endif

