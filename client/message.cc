#include <string>
#include "message.hh"
using namespace std;

// encMessage::encMessage
// Description - encMessage 생성자
// Return - None
encMessage::encMessage();

// encMessage::getNextIP
// Description - 해당 객체의 nextIP 변수의 값을 반환
// Return - String or Null
String encMessage::getNextIP();

// encMessage::getEncData
// Description - 해당 객체의 encData 변수의 값을 반환
// Return - BYTE* or Null
BYTE* encMessage::getEncData();

// encMessage::setNextIP
// Description - 해당 객체의 nextIP 변수에 값을 세팅
// Return - True / False
bool encMessage::setNextIP(String src);

// encMessage::setNextIP
// Description - 해당 객체의 encData 변수에 값을 세팅
// Return - True / False
bool encMessage::setEncData(BYTE* src);

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

}

// message::getGithubID
// Description - message 객체에서 GithubID 를 가져옴
// Return - message::getGithubID 값
String message::getGithubID(){

}

// message::getTimedtamp
// Description - message 객체에서 Timestamp를 가져옴
// Return - message::timestamp 값
long message::getTimestamp(){
}

// message::getOneTimeKey()
// Description - message 객체에서 OneTimeKey를 가져옴
// Return - message::OneTimeKey 값
BYTE* message::getOneTimeKey(){

}

// message::isWritable()
// Description - message 객체의 write가능 여부를 보여줌
// Return - message::writeable 값
bool message::isWritable(){
}

//////////////////// For Message Send ////////////////////

// message::setTimestamp
// Description - Writable Flag가 켜져있을 때 Timestamp 값을 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setTimestamp(long timestamp){
}

// message::setGithubID
// Description - Writable Flag가 켜져있을 때 GithubID를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setGithubID(String githubID){

}

// message::setOneTimeKey
// Description - Writeable Flag가 켜져있을 때 OneTimeKey를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setOneTimeKey(BYTE* OneTimeKey){

}

// message::setContents
// Description - Writable Flag가 켜져있을 때 GithubID를 message 객체에 기록
// Return - true = 성공, false = 실패
bool message::setContents(String content){

}

