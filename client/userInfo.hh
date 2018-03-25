#ifndef __userinfo__
#define __userinfo__

#include <iostream>
#include "nodelist.hh"

using namespace std;

class userInfo: public node {
public:
	userInfo(string GithubID, string PublicKeyID, string IP);
};

#endif
