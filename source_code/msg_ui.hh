#ifndef __MSG_UI__
#define __MSG_UI__
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <sys/ioctl.h>
#include <unistd.h>
// Added by elmisty
#include <termios.h>
#include "transmission.hh"
#include "nodelist.hh"
#include "timestamp.hh"
#include "parser.hh"
#include "gpg.hh"
 
using namespace std;


namespace msg_ui{

  struct arg_info{
    string senderID;
    nodelist* node_list;
  };

  void getRecvToMessageQueue(string you);

  void setDummyArgs(struct tmd::arg_data* send_args, string msg, nodelist* node_list, string recvID);

  int getBottomYLoc();
  void moveCursorLoc(int Y);
  void sendWrapper(string message, nodelist* node_list, string to);
  void cmd_execute(string ibuffer);
  void refresh_messages(string ibuffer,string sender);
  void* input_listener(void* args);
}
#endif
