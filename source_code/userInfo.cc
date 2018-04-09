#include "userInfo.hh"
using namespace std;

userInfo::userInfo(string GithubID, string PubKeyID, string IP, string Passphrase)
:node(GithubID, PubKeyID, IP) {
  this->Passphrase = Passphrase;
  this->mode = IDLE;
}

userInfo::userInfo():node(){}

string userInfo::getPassphrase(){
  return this->Passphrase;
}

void userInfo::setMode(int mode){
  this->mode = mode;
}

int userInfo::getMode(){
  return this->mode;
}

void userInfo::addMessage(message msg){
  this->msg_list.push_back(msg);
}

message userInfo::readMessage(){
  if(this->msg_list.size()!=0){
    message tmp((this->msg_list.front()).getContents(),(this->msg_list.front()).getGithubID(),(this->msg_list.front()).getOneTimeKey(),(this->msg_list.front()).getTimestamp());
    this->msg_list.pop_front();
    return tmp;
  }
  message tmp;
  return tmp;
}

