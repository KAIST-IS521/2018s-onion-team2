#include <iostream>
#include "userInfo.hh"
#include "nodelist.hh"
using namespace std;

userInfo::userInfo(string GithubID, string PublicKeyID, string IP)
:node(GithubID, PublicKeyID, IP) {

}
