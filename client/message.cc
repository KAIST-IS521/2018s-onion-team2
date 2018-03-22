#include <string>
#include "message.hh"
using namespace std;

// message::message
message::message(){

}

message::~message(){

}

// message::setMessage
// Description - message에 값을 할당하는 함수
// Return - true = 성공, false = 실패
bool message::setMessage(){

}

// message::getContents
// Description - message 객체에서 Chatting Contents를 가져옴
// Return - message::Content
String message::getContents(){
  return this->Content;
}

// message::getGithubID
// Description - message 객체에서 GithubID 를 가져옴
// Return - message::getGithubID 값
String message::getGithubID(){
  return this->GithubID;
}

// message::getTimedtamp
// Description - message 객체에서 Timestamp를 가져옴
// Return - message::timestamp 값
long message::getTimestamp(){
  return this->timestamp;
}

// message::getOneTimeKey()
// Description - message 객체에서 OneTimeKey를 가져옴
// Return - message::OneTimeKey 값
BYTE* message::getOneTimeKey(){
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
bool message::setTimestamp(long timestamp){
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
bool message::setOneTimeKey(BYTE* OneTimeKey){
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
