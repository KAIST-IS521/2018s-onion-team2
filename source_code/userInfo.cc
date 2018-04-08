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
  // UI
}

message userInfo::readMessage(){
  //message* deleted_pointer;
//  cout << " READ MSG " << endl;
  if(this->msg_list.size()!=0){
//    cout << "It has a message!" << endl;
    message tmp((this->msg_list.front()).getContents(),(this->msg_list.front()).getGithubID(),(this->msg_list.front()).getOneTimeKey(),(this->msg_list.front()).getTimestamp());
    //deleted_pointer= &(this->msg_list.front());
    //tmp = new message(deleted_pointer->getContents(),deleted_pointer->getGithubID(),deleted_pointer->getOneTimeKey(), deleted_pointer->getTimestamp());
 //   cout << "ID : " << tmp.getGithubID()<<endl;
   // cout << "MSG : " << tmp.getContents()<<endl;
    this->msg_list.pop_front(); // it delete deleted_pointer, plz no "delete deleted_pointer"
   // cout << "READ MSG OUT" << endl;
    return tmp;
  }
  message tmp;
//  cout << "READ MSG OUT" << endl;
  // UI
  return tmp;
}

