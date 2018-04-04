#include <iostream>
#include <unistd.h>
#include <string>
#include "../source_code/transmission.hh"
using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " -p [PORT] -m [MESSAGE] -k [PUBKEYID] -P [PASSPHRASE]" << endl;
  exit(0);
};

int main(int argc, char* const argv[]){
  int opt;
  int port = -1;
  string message = "";
  string pubKeyId = "";
  string passphrase = "";
  
  while((opt = getopt(argc, argv, "p:m:k:P:h")) != -1){
    switch(opt){
      case 'p':
        // Set a port
        port = atoi(optarg);
        break;
      case 'm':
        // Set a message
        message = optarg;
        break;
      case 'k':
        // Set a user's pubkeyid
        pubKeyId = optarg;
        break;
      case 'P':
        passphrase = optarg;
        break;
      case 'h':
        // Print help message
        printHelp(argv);
        break;
    }
  }
  
  // Wrong use of arguments
  if(port == -1 || message == "" || pubKeyId == "" || passphrase == "") {
    printHelp(argv);
    return 1;
  }

  // Create an argument setting for the listening thread
  struct tmd::arg_main* listen_args = new struct tmd::arg_main();
  tmd::msg_args(listen_args);

  // Create an thread for the listening
  pthread_t th_listen;
  pthread_create(&th_listen, NULL, tmd::tmdReceiverMain, (void*)listen_args);

  // Create an argument seting for the sending thread
  struct tmd::arg_data* send_args  = new struct tmd::arg_data();
//  parser::packListUpdate(SIGN_IN, list_update_arguments);

  // Create an thread for the listening
  pthread_t th_send;
  pthread_create(&th_send, NULL, tmd::tmdSender, (void*)send_args);

  return 0;
}
