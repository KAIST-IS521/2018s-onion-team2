#ifndef __userinfo__
#define __userinfo__

#include "nodelist.hh"

using namespace std;

class userInfo: public node {
private:
  string Passphrase;
  // Need a list that contains unread messages
public:
  userInfo(string GithubID, string PublicKeyID, string IP, string Passphrase);
};

#endif
