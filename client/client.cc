#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include "../source_code/transmission.hh"
#include "../source_code/timestamp.hh"
#include "../source_code/parser.hh"
using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " [-p PASSPHRASE] [-k PUBKEYID(RECEIVER) -m MESSAGE -r PATH TO RECEIVER]" << endl;
  cout << "Using ':' as a delimiter, routing path should be specified with ip addresses" << endl;
  cout << "Do not include  sender's ip address in the routing path" << endl;
  exit(0);
}

// Set dummy arguments
void setDummyArgs(struct tmd::arg_data* send_args, string msg, string path){
  list<string> ip_list;
  char *ch = strtok((char*)path.c_str(), ":");

  while (ch != NULL)
  {
    // parse the path and store it as a stack
    ip_list.push_front(ch);
    ch = strtok(NULL, ":");
  }

  // For the final client
  send_args->IP = ip_list.back();
  ip_list.pop_back();

  message _msg;
  _msg.setContents(msg);
  _msg.setGithubID("leeswimming");
  _msg.setOneTimeKey();
  _msg.setTimestamp(timestamp::getTimestampNow());

  char* stream = new char[parser::getMessagePackLen(&_msg)];
  parser::packMessage(stream, &_msg, ip_list.front());

  // For clients in the routing path excluding the final clients
  encMessage encMsg;
  for(list<string>::iterator it = ip_list.begin(); it != ip_list.end(); it++){
    encMsg.setNextIP(*it);
    encMsg.setEncData(stream);
    delete stream;
    stream = new char[parser::getEncMessagePackLen(&encMsg)];
    parser::packEncMessage(stream, &encMsg);
  }
  
  send_args->length = parser::getEncMessagePackLen(&encMsg);
  send_args->data = new char[send_args->length];
  memcpy(send_args->data, stream, send_args->length);
  delete stream;
}

int main(int argc, char* const argv[]){
  int opt;
  string message = "";
  string pubKeyId = "";
  string passphrase = "";
  string path = "";
  
  while((opt = getopt(argc, argv, "p:m:k:P:r:h")) != -1){
    switch(opt){
      case 'm':
        // Set a message
        message = optarg;
        break;
      case 'k':
        // Set an user's pubkeyid
        pubKeyId = optarg;
        break;
      case 'p':
        // Set a passphrase
        passphrase = optarg;
        break;
      case 'r':
        path = optarg;
        break;
      case 'h':
        // Print help message
        printHelp(argv);
        break;
    }
  }

  if((pubKeyId != "" && message != "" && path != "") || (passphrase != "")){
    /* 
        Receiver should specify passphrase
        Sender should specify message, path and receiver's pubKeyID
    */
    printHelp(argv);
    return 1;
  }

  // Set a dummy user info
  user = userInfo("leeswimming", pubKeyId, "", passphrase);

  if(message == ""){
    // Create an argument setting for the listening thread
    struct tmd::arg_main* listen_args = new struct tmd::arg_main();
    tmd::msg_args(listen_args);

    // Create a thread for the listening
    pthread_t th_listen;
    pthread_create(&th_listen, NULL, tmd::tmdReceiverMain, (void*)listen_args);
    pthread_join(th_listen, NULL);
  } else {
    // Create an argument seting for the sending thread
    struct tmd::arg_data* send_args  = new struct tmd::arg_data();
    setDummyArgs(send_args, message, path);

    // Create a thread for the listening
    pthread_t th_send;
    pthread_create(&th_send, NULL, tmd::tmdSender, (void*)send_args);
    pthread_join(th_send, NULL);
  }

  return 0;
}
