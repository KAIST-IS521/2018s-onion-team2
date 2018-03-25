#ifndef __nodelist__
#define __nodelist__

#include <list>
#include <iostream>

using namespace std;

class node{
private:
  string GithubID;
  string PubKeyID;
  string IP;
public:
  node(char* datastream);
  node(string _GithubID, string PubKeyID, string IP);
  string getGithubID();
  string getPubKeyID();
  string getIP();
};

class nodelist{
private:
  list<node> _nodelist;
  //time_t updatetime; // 필요 있을까...?
public:
  nodelist(node first_node);
  node* searchNode(string GithubID);
  // node* searchNode(string IP);
  bool deleteNode(string GithubID);
  // bool deleteNode(string IP);
  int getNodelistLen();
  list<node*> getRandomNode(int count);
  //int getLastUpdateTime(); // 필요 있을까...?
  bool appendNode(node append_node);
};

#endif
