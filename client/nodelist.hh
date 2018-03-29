#ifndef __nodelist__
#define __nodelist__

#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#define NL_GITHUBID 0
#define NL_IP 1

using namespace std;

class node{
private:
  string GithubID;
  string PubKeyID;
  string IP;
public:
  node(string _GithubID, string PubKeyID, string IP);
  string getGithubID();
  string getPubKeyID();
  string getIP();
};

class nodelist{
private:
  list<node*>* _nodelist;
public:
  nodelist();
  node* searchNode(string value,int mode);
  bool deleteNode(string value,int mode);
  int getNodelistLen();
  node* getRandomNode();
  bool appendNode(node* append_node);
  vector<string>* getGithubIDList();
};
#endif