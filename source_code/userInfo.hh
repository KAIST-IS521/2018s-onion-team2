#ifndef __userinfo__
#define __userinfo__

#include "nodelist.hh"

using namespace std;

class userInfo: public node {
private:
  string Passphrase;
  // Need a list that contains unread messages
public:
  userInfo();
  userInfo(string GithubID, string PubKeyID, string IP, string Passphrase);
  string getPassphrase();
};

#endif
