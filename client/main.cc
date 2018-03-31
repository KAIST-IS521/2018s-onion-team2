#include "ui.hh"
#include "userInfo.hh"
#include "transmission.hh"
#include "heartbeat.hh"
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
  
  userInfo user = ui::login();
  
  struct arg_main* msg_arguments = new struct arg_main;
  msg_args(user, msg_arguments);

  struct arg_main* hearbeat_arguments = new struct arg_main;
  hbd::heartbeat_args(user, hearbeat_arguments);
  
  pthread_t th_msg, th_heartbeat;
  pthread_create(&th_msg; NULL, tmd::tmdReciverMain, (void*)msg_arguments);
  pthread_create(&th_heartbeat, NULL, tmd::tmdReciverMain, (void*)hearbeat_arguments);

  pthread_join(th_msg, NULL);
  pthread_join(th_heartbeat, NULL);
  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening
  return 0;
}