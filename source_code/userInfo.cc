#include <iostream>
#include "userInfo.hh"
#include "nodelist.hh"
using namespace std;

userInfo::userInfo(string GithubID, string PubKeyID, string IP, string Passphrase)
:node(GithubID, PubKeyID, IP) {
  this->Passphrase = Passphrase;
}

userInfo::userInfo():node(){}

string userInfo::getPassphrase(){
  return this->Passphrase;
}

void userInfo::addMessage(message msg){
  this->msg_list.push_back(msg);
  // UI
}

message userInfo::readMessage(){
  message tmp = this->msg_list.front();
  this->msg_list.pop_front();
  // UI
  return tmp;
}