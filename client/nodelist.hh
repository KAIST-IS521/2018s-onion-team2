#ifndef __nodelist__
#define __nodelist__

#include <iostream>
#include <list>
#include <cstdlib>

using namespace std;

class node(){
private:
  string GithubID;
  string PubKeyID;
  string IP;
public:
  node(string _GithubID, String PubKeyID, String IP);
  string getGithubID();
  string getPubKeyID();
  string getIP();
}

class nodelist(){
private:
  list<node*> nodelist;
public
  nodelist(node* first_node);
  node* searchNode(string GithubID);
  node* searchNode(string IP);
  bool deleteNode(string GithubID);
  bool deleteNode(string IP);
  int getNodelistLen();
  list* getRandomNode();
  bool appendNode(node* append_node);
}
#endif
