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
  char buffer[10];
  try{
    int socketFd = socket(AF_INET, SOCK_DGRAM,0);
    if(-1 == sock)
    { 
      return NULL;
    }
  
    struct sockaddr_in server_info;
    memset(&server_info,0,sizeof(server_info)); // initalize server_info to 0
    server_info.sin_family=AF_INET;
    server_info.sin_port = htons(60000);              // discuss about it ### PORT ###
    server_info.sin_adr.s_addr=inet_addr("127.0.0.1"); // discuss about it ### SERVER IP ###

    if(-1 == bind(socketFd,(struct sockaddr*)&server_addr,sizeof(server_addr))){
      return NULL;
    }
    recvfrom(socketFd, &buffer, 10,0,(struct sockaddr*)&server_info,sizeof(server_info));
    if(buffer[0]!=0x04){
      return NULL; // check check check
    }
    close(socketFd);
  }
  catch(){
    return NULL;
  }
  return buffer;

}

// hbd::heartbeatListener
// Description - heartbeat 메세지 송신대기 함수
// return - None
void hbd::heartbeatListener()
{
  while(true){
    try{
      char* gotData = recvHeartbeat();
      if(gotData!=NULL){
        heartbeat parsedData = new heartbeat(gotData);
        parsedData.setTimestamp(timestamp::getTimestampNow());                                // timestamp 함수 제작 요
        char* packedData = parser::packHeartBeat(&parsedData);
        
        if(packedData!=NULL){
        sendHeartbeat(packedData);
        
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
bool hbd::sendHeartbeat(char* send_source, int send_size)
{
  try{
    int socketFd = socket(AF_INET, SOCK_DGRAM,0);
    if(-1 == sock)
    {
      return false;
    }
  
    struct sockaddr_in server_info;
    memset(&server_info,0,sizeof(server_info)); // initalize server_info to 0
    server_info.sin_family=AF_INET;
    server_info.sin_port = htons(60000);              // discuss about it ### PORT ###
    server_info.sin_addr.s_addr=inet_addr("127.0.0.1"); // discuss about it ### SERVER IP ###
  
    sendto(socketFd, send_source, send_size+1,0,(struct sockaddr*)&server_info,sizeof(server_info));
  }
  catch(){
    close(socketFd);
    return false;
  }
  close(socketFd);
  return true;
}
