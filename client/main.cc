#include "ui.hh"
#include "userInfo.hh"
#include "transmission.hh"
#include "heartbeat.hh"
#include <pthread.h>
#include <netinet/in.h>
using namespace std;

int main(int argc, char const *argv[])
{
  
  userInfo user = ui::login();
  
  struct tmd::arg_main* msg_arguments = new struct tmd::arg_main;
  tmd::msg_args(user, msg_arguments);

  struct tmd::arg_main* hearbeat_arguments = new struct tmd::arg_main;
  hbd::heartbeat_args(user, hearbeat_arguments);
  
  pthread_t th_msg, th_heartbeat;
  pthread_create(&th_msg, NULL, tmd::tmdReciverMain, (void*)msg_arguments);
  pthread_create(&th_heartbeat, NULL, tmd::tmdReciverMain, (void*)hearbeat_arguments);

  pthread_join(th_msg, NULL);
  pthread_join(th_heartbeat, NULL);

  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening
  return 0;
}