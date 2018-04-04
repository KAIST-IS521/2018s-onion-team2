#include <iostream>
#include <unistd.h>
#include <string>
#include "../source_code/transmission.hh"
using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " -p PORT -k PUBKEYID -P PASSPHRASE [-m MESSAGE -r PATH TO RECEIVER]" << endl;
  cout << "Using ':' as a delimiter, routing path should be specified with port numbers" << endl;
  exit(0);
}

// Set dummy arguments
void setDummyArgs(struct tmd::arg_data* send_args, string message, string path){
  send_args->IP = "127.0.0.1";
  send_args->path = path;  
  send_args->length = message.length();
  send_args->data = new char[send_args->length];
  memcpy(send_args->data, message.c_str(), send_args->length);
}

int main(int argc, char* const argv[]){
  int opt;
  int port = -1;
  string message = "";
  string pubKeyId = "";
  string passphrase = "";
  string path = "";
  
  while((opt = getopt(argc, argv, "p:m:k:P:r:h")) != -1){
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
        // Set an user's pubkeyid
        pubKeyId = optarg;
        break;
      case 'P':
        // Set a passphrase
        passphrase = optarg;
        break;
      case 'h':
        // Print help message
        printHelp(argv);
        break;
    }
  }
  
  if(port == -1 || || pubKeyId == "" || passphrase == "") {
    /* Mandatory options */
    printHelp(argv);
    return 1;
  } else if((message == "" and path != "") or (message != "" and path == "")){
    /* 
        Optional options
        Sender should specify both a message and a path
    */
    return 2;
  }

  // Set a dummy user info
  user = UserInfo("dummy", pubKeyId, "127.0.0.1", passphrase);

  if(message == ""){
    // Create an argument setting for the listening thread
    struct tmd::arg_main* listen_args = new struct tmd::arg_main();
    tmd::msg_args(listen_args);

    // Create a thread for the listening
    pthread_t th_listen;
    pthread_create(&th_listen, NULL, tmd::tmdReceiverMain, (void*)listen_args);
  } else {
    // Create an argument seting for the sending thread
    struct tmd::arg_data* send_args  = new struct tmd::arg_data();
    setDummyArgs(send_args, message, path);

    // Create a thread for the listening
    pthread_t th_send;
    pthread_create(&th_send, NULL, tmd::tmdSender, (void*)send_args);
  }
  return 0;
}
