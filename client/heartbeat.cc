#include "heartbeat.hh"
using namespace std;
// heartbeat::heartbeat
// Description - heartbeat 생성자
// return - None
heartbeat::heartbeat(char* _OneTimeKey, time_t _timestamp){
  this->OneTimeKey = _OneTimeKey;
  this->timestamp = _timestamp;
}


// heartbeat::getOneTimeKey
// Description - heartbeat 객체에서 OntTimeKey를 가져옴
// return - Null(실패), char*(OneTimeKey stream)
char* heartbeat::getOneTimeKey(){
  return this->OneTimeKey;
}

// heartbeat::getTimestamp
// Description - heartbeat 객체에서 Timestamp를 가져옴
// return - Null(실패), time_t(Timestamp)
time_t heartbeat::getTimestamp(){
  return this->timestamp;
}


// heartbeat::setOneTimeKey
// Description - heartbeat 객체에 OntTimeKey를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setOneTimeKey(char* _OneTimeKey){
  try{
    this->OneTimeKey = _OneTimeKey;
    return true;
  }
  catch(int exception){
    return false;
  }
} 


// heartbeat::recvHeartbeat
// Description - heartbeat 객체에 Timestamp를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setTimestamp(time_t _timestamp){
  try{
    this->timestamp = _timestamp;
    return true;
  }
  catch(int exception){
    return false;
  }
}

// hbd::recvHeartbeat
// Description - 서버로부터 heartbeat 메시지를 받아 처리하는 함수
// return - Null(실패), char*
void* hbd::recvHeartbeat((void*)args)
{
  string message = "";
  int n;
  char data[HB_LEN];
  struct arg_receiver *arguments = (struct arg_receiver *)args;
  int recvFd = arguments->recvFd;
  string IP = arguments->IP;
  delete (struct arg_receiver *)args;
  pthread_detach(pthread_self());

  n = read(recvFd, data, HB_LEN);

  if(n == HB_LEN && IP == SERVER_ADDR && data[0] == '\x04'){
    char response[HB_LEN];
    hbd::setHeartBeat(data, response);
    write(recvFd, response, HB_LEN);
  }
  close(recvFd);
}

// hbd::SendHeartbeat
// Description - 서버에게 heartbeat 메시지를 전달하는 함수
// return - 전달했으면 true, 아니면 false
bool hbd::sendHeartbeat(char* send_source, int send_size)
{
  char* buf;
  int recvFd;
  int sockFd = socket(AF_INET, SOCK_DGRAM,0);

  if (sockFd < 0){
    return false;
  }
  struct sockaddr_in sock_info, conn_info;
  int conn_len = sizeof(conn_info);
  bzero((char*)&sock_info, sizeof(sock_info));
  sock_info.sin_family = AF_INET;
  sock_info.sin_addr.s_addr = HB_SERVER_ADDR;
  sock_info.sin_port = htons(HB_PORT);

  if (0 > connect(sockFd,(struct sockaddr *) &sock_info,sizeof(sock_info))){
    return false;
  }

  if (0 >  send(sockFd,send_source,send_size,0)){
    return false;
  }
  close(sockFd);
  return true;
}
