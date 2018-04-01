#include "ui.hh"
#include "userInfo.hh"
#include "transmission.hh"
#include "heartbeat.hh"
#include "parser.hh"
#include <pthread.h>
#include <netinet/in.h>
using namespace std;

int main()
{
  user = ui::login();
  
  struct tmd::arg_main* msg_arguments = new struct tmd::arg_main();
  tmd::msg_args(msg_arguments);

  struct tmd::arg_main* hearbeat_arguments = new struct tmd::arg_main();
  hbd::heartbeat_args(hearbeat_arguments);

  struct tmd::arg_data* list_update_arguments = new struct tmd::arg_data();
  parser::packListUpdate(SIGN_IN, list_update_arguments);
  
  pthread_t th_msg, th_heartbeat, th_list_update, th_input;
  pthread_create(&th_msg, NULL, tmd::tmdReceiverMain, (void*)msg_arguments);
  pthread_create(&th_heartbeat, NULL, tmd::tmdReceiverMain, (void*)hearbeat_arguments);
  pthread_create(&th_list_update, NULL, tmd::tmdSender, (void*)list_update_arguments);
  pthread_create(&th_input, NULL, ui::userInput, NULL);

  pthread_join(th_msg, NULL);
  pthread_join(th_heartbeat, NULL);
  pthread_join(th_list_update, NULL);
  pthread_join(th_input, NULL);

  return 0;
}