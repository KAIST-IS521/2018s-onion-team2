#ifndef __userinfo__
#define __userinfo__

#include "nodelist.hh"
#include "message.hh"
#include <iostream>
#include <list>
using namespace std;

class userInfo: public node {
private:
  string Passphrase;
  list<message> msg_list;
public:
  userInfo();
  userInfo(string GithubID, string PubKeyID, string IP, string Passphrase);
  void addMessage(message msg);
  message readMessage();
  string getPassphrase();
};

#endif
