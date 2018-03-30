#include <string>
#include "message.hh"
using namespace std;

// encMessage::encMessage
// Description - encMessage 생성자
// Return - None
encMessage::encMessage(){
  this->nextIP = NULL;
  this->encData = NULL;
}

// encMessage::getNextIP
// Description - 해당 객체의 nextIP 변수의 값을 반환
// Return - String or Null
string encMessage::getNextIP(){
  return this->nextIP;
}

// encMessage::getEncData
// Description - 해당 객체의 encData 변수의 값을 반환
// Return - char* or Null
string encMessage::getEncData(){
  return this->encData;
}

// encMessage::setNextIP
// Description - 해당 객체의 nextIP 변수에 값을 세팅
// Return - True / False
bool encMessage::setNextIP(String src){
  try{
    this->nextIP = src;
  }
  catch(){
    return false;
  }
  return true;
}

// encMessage::setNextIP
// Description - 해당 객체의 encData 변수에 값을 세팅
// Return - True / False
bool encMessage::setEncData(string src){
  try{
    this->encData = src
  }
  catch(){
    return false;
  }
  return true;
}

// message::message
message::message(){
  this->Content = NULL;
  this->GithubID = NULL;
  this->OneTimeKey = NULL;
  this->timestamp = 0;
  this->writable = true;
}

// message::getContents
// Description - message 객체에서 Chatting Contents를 가져옴
// Return - message::Content
string message::getContents(){
  return this->Content;
}

// message::getGithubID
// Description - message 객체에서 GithubID 를 가져옴
// Return - message::getGithubID 값
string message::getGithubID(){
  return this->GithubID;
}

// message::getTimedtamp
// Description - message 객체에서 Timestamp를 가져옴
// Return - message::timestamp 값
time_t message::getTimestamp(){
  return this->timestamp;
}

// message::getOneTimeKey()
// Description - message 객체에서 OneTimeKey를 가져옴
// Return - message::OneTimeKey 값
char* message::getOneTimeKey(){
  return this->OneTimeKey;
}

// message::isWritable()
// Description - message 객체의 write가능 여부를 보여줌
// Return - message::writeable 값
bool message::isWritable(){
  return this->writable;
}

//////////////////// For Message Send ////////////////////

// message::setTimestamp
// Description - Writable Flag가 켜져있을 때 Timestamp 값을 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setTimestamp(time_t timestamp){
  if (isWritable()){
    this->timestamp = timestamp;
    return true;
  }
  else{
    return false;
  }
}

// message::setGithubID
// Description - Writable Flag가 켜져있을 때 GithubID를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setGithubID(String GithubID){
  if (isWritable()){
    this->GithubID = GithubID;
    return true;
  }
  else{
    return false;
  }
}

// message::setOneTimeKey
// Description - Writeable Flag가 켜져있을 때 OneTimeKey를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setOneTimeKey(char* OneTimeKey){
  if (isWritable()){
    this->OneTimeKey = OneTimeKey;
    return true;
  }
  else{
    return false;
  }
}

// message::setContents
// Description - Writable Flag가 켜져있을 때 GithubID를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setContents(String Content){
  if (isWritable()){
    this->Content = Content;
    return true;
  }
  else{
    return false;
  }
}
