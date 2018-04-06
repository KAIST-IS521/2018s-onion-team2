#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include "../source_code/transmission.hh"
#include "../source_code/timestamp.hh"
#include "../source_code/parser.hh"
#include "../source_code/gpg.hh"
#include "../source_code/nodelist.hh"
using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " [-p PASSPHRASE] [-m MESSAGE -r PATH TO RECEIVER]" << endl;
  cout << "Using ':' as a delimiter, routing path should be specified with ip addresses" << endl;
  cout << "Do not include  sender's ip address in the routing path" << endl;
  exit(0);
}

// Set dummy arguments
void setDummyArgs(struct tmd::arg_data* send_args, string msg, nodelist* node_list, string path){
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

  message _msg;
  _msg.setContents(msg);
  _msg.setGithubID("Donovan");
  _msg.setOneTimeKey();
  _msg.setTimestamp(timestamp::getTimestampNow());

  // Convert the message into a protocol
  int stream_len = parser::getMessagePackLen(&_msg);
  char* stream = new char[stream_len];
  char* tmp_stream = stream;
  parser::packMessage(stream, &_msg, ip_list.front());

  // Encrypting the message
  node* node = node_list->searchNode(ip_list.front(), 1);
  string pubKeyId = node->getPubKeyID();
  stream = gpg::encBytestream(stream, &pubKeyId, stream_len);
  delete tmp_stream;

  encMessage encMsg;
  for(list<string>::iterator it = ip_list.begin(); (++it)-- != ip_list.end(); it++){
    // For clients in the routing path excluding the final clients
    encMsg.setNextIP(*it);
    encMsg.setEncData(stream);
    delete stream;

    // Convert the message into a protocol
    stream_len = parser::getEncMessagePackLen(&encMsg);
    stream = new char[stream_len];
    parser::packEncMessage(stream, &encMsg);

    // Encrypting the message
    node = node_list->searchNode(*((++it)--), 1);
    pubKeyId = node->getPubKeyID();
    tmp_stream = stream;
    stream = gpg::encBytestream(stream, &pubKeyId, stream_len);
    delete tmp_stream;
  }
  
  send_args->length = string(stream).length();
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

  while((opt = getopt(argc, argv, "p:m:r:h")) != -1){
    switch(opt){
      case 'm':
        // Set a message
        message = optarg;
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

  if(!(message != "" && path != "") && !(passphrase != "")){
    /* 
        Receiver should specify passphrase
        Sender should specify message, path
    */
    printHelp(argv);
    return 1;
  }

  nodelist* node_list = new nodelist();

  node* node1 = new node("Donovan","9932355F","172.20.0.2");
  node* node2 = new node("Marvin","704DB4C6","172.20.0.3");
  node* node3 = new node("Stanton","BBB8EA0C","172.20.0.5");
  node* node4 = new node("Sandra","60003972","172.20.0.4");
  node* node5 = new node("Jason","BC1B3BC4","172.20.0.6");

  node_list->appendNode(node1);
  node_list->appendNode(node2);
  node_list->appendNode(node3);
  node_list->appendNode(node4);
  node_list->appendNode(node5);

  // Set a dummy user info
  user = userInfo("Donovan", "", "", passphrase);


  // Create an argument setting for the listening thread
  struct tmd::arg_main* listen_args = new struct tmd::arg_main();
  tmd::msg_args(listen_args);

  // Create a thread for the listening
  pthread_t th_listen;
  pthread_create(&th_listen, NULL, tmd::tmdReceiverMain, (void*)listen_args);
  // pthread_join(th_listen, NULL); /* This thread is detached */
  
  // Create an argument seting for the sending thread
  struct tmd::arg_data* send_args  = new struct tmd::arg_data();
  setDummyArgs(send_args, message, node_list, path);

  // Create a thread for the listening
  pthread_t th_send;
  pthread_create(&th_send, NULL, tmd::tmdSender, (void*)send_args);
  pthread_join(th_send, NULL);

  while(true){
    /*
      This is a dummy inifinite loop
      to prevent other threads from being terminated
      due to termination of the main thread.

      This loop can be replaced to get user inputs from stdin.
    */
  }

  delete node1;
  delete node2;
  delete node3;
  delete node4;
  delete node5;
  delete node_list;

  return 0;
}
