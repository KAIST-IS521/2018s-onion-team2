#ifndef __nodelist__
#define __nodelist__
#define BYTE unsigned char

#include <list>

using namespace std;

class node(){
private:
  String GithubID;
  String PubKeyID;
  String IP;
public:
  node();
  node(BYTE* datastream);
  node(String _GithubID, String PubKeyID, String IP);
  String getGithubID();
  String getPubKeyID();
  String getIP();
}

class nodelist(){
private:
  list<node> nodelist;
  //long updatetime; // 필요 있을까...?
public
  nodelist(node first_node);
  node* searchNode(String GithubID);
  node* searchNode(String IP);
  bool deleteNode(String GithubID);
  bool deleteNode(String IP);
  int getNodelistLen();
  int setNodelistLen();
  //int getLastUpdateTime(); // 필요 있을까...?
  bool appendNode(node append_node);
}
#endif
