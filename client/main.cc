#include "ui.hh"
#include "userInfo.hh"
#include "transmission.hh"
#include <pthread.h>
using namespace std;

int main(int argc, char const *argv[])
{
  pthread_t th_node_list;
  userInfo user = ui::login();
  pthread_create(&th_node_list, NULL, tmd::tmdReciverMain, (void*)&user);
  pthread_join(th_node_list, NULL);
  
  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening
  return 0;
}