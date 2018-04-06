#ifndef __userinfo__
#define __userinfo__

#include "nodelist.hh"
#include "message.hh"
#include <iostream>
#include <list>
#define IDLE 0
#define CHAT 1
using namespace std;

class userInfo: public node {
private:
  string Passphrase;
  list<message> msg_list;
  int mode;
public:
  userInfo();
  userInfo(string GithubID, string PubKeyID, string IP, string Passphrase);
  void addMessage(message msg);
  message* readMessage();
  string getPassphrase();
  void setMode(int mode);
  int getMode();
};

#endif
