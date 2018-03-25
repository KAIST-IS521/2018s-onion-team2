#ifndef __userinfo__
#define __userinfo__

#include <iostream>
#include "nodelist.hh"

using namespace std;

class userInfo: public node {
private:
  string Passphrase;
public:
  userInfo(string GithubID, string PublicKeyID, string IP, string Passphrase);
};

#endif
