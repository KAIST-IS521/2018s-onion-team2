#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdio.h>

#include "../source_code/transmission.hh"
#include "../source_code/util.hh"
#include "../source_code/timestamp.hh"
#include "../source_code/parser.hh"
#include "../source_code/gpg.hh"
#include "../source_code/nodelist.hh"
#include "../source_code/msg_ui.hh"
#include "../source_code/ui.hh"

using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " [-p PASSPHRASE] [-m MESSAGE -r RECEIVER ID]" << endl;
  exit(0);
}


int main(int argc, char* const argv[]){
  int opt;
  char key;
  string pubKeyId = "";
  string passphrase = "";
  string to = "";

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

  user = ui::login(node_list);

  // Create an argument setting for the listening thread
  struct tmd::arg_main* listen_args = new struct tmd::arg_main();
  tmd::msg_args(listen_args,user.getGithubID());

  // Create a thread for the listening
  pthread_t th_listen;
  pthread_create(&th_listen, NULL, tmd::tmdReceiverMain, (void*)listen_args);
  
  msg_ui::input_listener(user.getGithubID(), node_list);

  delete node1;
  delete node2;
  delete node3;
  delete node4;
  delete node5;
  delete node_list;

  return 0;
}
