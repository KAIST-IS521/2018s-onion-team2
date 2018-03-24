#include "heartbeat.hh"



// heartbeat::heartbeat
// Description - heartbeat 생성자
// return - None
heartbeat::heartbeat(char* _OneTimeKey, time_t _timestamp){
  this.OneTimeKey = _OneTimeKey;
  this.timestamp = _timestamp;
}

// heartbeat::getOneTimeKey
// Description - heartbeat 객체에서 OntTimeKey를 가져옴
// return - Null(실패), char*(OneTimeKey stream)
char* heartbeat::getOneTimeKey(){
  return this.OneTimeKey;
}

// heartbeat::getTimestamp
// Description - heartbeat 객체에서 Timestamp를 가져옴
// return - Null(실패), time_t(Timestamp)
time_t heartbeat::getTimestamp(){
  return this.timestamp;
}


// heartbeat::setOntTimeKey
// Description - heartbeat 객체에 OntTimeKey를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setOntTimeKey(char* _OneTimeKey){
  try{
    this.OneTimeKey = _OneTimeKey;
    return true;
  }
  catch(){
    return false;
  }
} 


// heartbeat::recvHeartbeat
// Description - heartbeat 객체에 Timestamp를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setTimestamp(time_t _timestamp){
  try{
    this.timestamp = timestamp;
    return true;
  }
  catch(){
    return false;
  }
}

// hbd::recvHeartbeat
// Description - 서버로부터 heartbeat 메시지를 받아 처리하는 함수
// return - Null(실패), char*
char* hbd::recvHeartbeat()
{
  
}

// hbd::heartbeatListener
// Description - heartbeat 메세지 송신대기 함수
// return - None
void hbd::heartbeatListener(string ip,int port)
{
  while(true){
    try{
      char* gotData = recvHeartbeat();
      if(gotData!=NULL){
        heartbeat parsedData = new heartbeat(gotData);
        parsedData.setTimestamp(??);                                // timestamp 함수 제작 요
        char* packedData = parser::packHeartBeat(&parsedData);
        
        if(packedData!=NULL){
        sendHeartbeat(ip,port,packedData);
        
        }
        else{
          throw;
        }        
      }
    }
    catch(){

    }
    delete parsedData;
  }
}

// hbd::SendHeartbeat
// Description - 서버에게 heartbeat 메시지를 전달하는 함수
// return - 전달했으면 true, 아니면 false
bool hbd::sendHeartbeat(char* send_source)
{

}
