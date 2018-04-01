#include "list_check.hh"
#include "nodelist.hh"
#include "hb_server.hh"
#include <iostream>
#include <list>
#include <pthread.h>

int main() {

  struct lstd::arg_main* list_update_arguments = new struct lstd::arg_main();
  lstd::server_msg_args(list_update_arguments);

  pthread_t th_list_update, th_heartbeat;
  pthread_create(&th_list_update, NULL, lstd::listReceiverMain, (void*)list_update_arguments);
  pthread_create(&th_heartbeat, NULL, hbchecker::hbCheckerMain, NULL);

	pthread_join(th_list_update, NULL);
	pthread_join(th_heartbeat, NULL);
		
	return 0;	
}

