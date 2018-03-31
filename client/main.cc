#include "ui.hh"
#include "userInfo.hh"
#include "transmission.hh"
#include <pthread.h>
#include <netinet/in.h>
using namespace std;


void msg_args(userInfo user, struct arg_main* arguments){
  arguments->port = MESSAGE_PORT;
  arguments->protocol = IPPROTO_TCP;
  arguments->type = SOCK_STREAM;
  arguments->user = user;
  arguments->func = tmd::tmdReciver;
}

int main(int argc, char const *argv[])
{
  pthread_t th_node_list;
  userInfo user = ui::login();
  struct arg_main* msg_arguments = new struct arg_main;
  msg_args(user, msg_arguments);
  pthread_create(&th_node_list, NULL, tmd::tmdReciverMain, (void*)msg_arguments);
  pthread_join(th_node_list, NULL);
  
  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening
  return 0;
}