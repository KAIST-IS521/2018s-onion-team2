#ifndef __TRANSMISSION__
#define __TRANSMISSION__
#include "gpg.hh"
#include "nodelist.hh"
#include "util.hh"

#include <netdb.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <list>

using namespace std;

// tmd = TransMission Daemon
namespace tmd{
  struct arg_main {
    int protocol;
    int port;
    int type;
    string you;
    void*(*func)(void*);
  };

  struct arg_receiver {
    int recvFd;
    string IP;
    string you;
    char buf[HB_LEN];
  };

  struct arg_data {
    char* data;
    int length;
    string IP;
  };

  void* tmdReceiver(void* args);
  void* tmdReceiverMain(void* args);
  void msg_args(struct arg_main* arguments,string hostid);
  void data_args(string IP, char* data, struct arg_data* list_update_arguments);
  list<node*> tmdPathSelecter();
  void* tmdSender(void* args);
  // char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
};

#endif
