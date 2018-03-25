#include <iostream>
#include "userInfo.hh"
#include "nodelist.hh"
using namespace std;

userInfo::userInfo(string GithubID, string PublicKeyID, string IP, string Passphrase)
:node(GithubID, PublicKeyID, IP) {
	this->Passphrase;
}
