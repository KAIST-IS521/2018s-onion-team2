#ifndef __nodelist__
#define __nodelist__

#include <list>

using namespace std;

class node(){
private:
  string GithubID;
  string PubKeyID;
  string IP;
public:
  node();
  node(char* datastream);
  node(string _GithubID, String PubKeyID, String IP);
  string getGithubID();
  string getPubKeyID();
  string getIP();
}

class nodelist(){
private:
  list<node> nodelist;
  //time_t updatetime; // 필요 있을까...?
public
  nodelist(node first_node);
  node* searchNode(string GithubID);
  node* searchNode(string IP);
  bool deleteNode(string GithubID);
  bool deleteNode(string IP);
  int getNodelistLen();
  //int getLastUpdateTime(); // 필요 있을까...?
  bool appendNode(node append_node);
}
#endif
