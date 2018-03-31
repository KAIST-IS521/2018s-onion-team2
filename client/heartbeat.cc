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
char* hbd::recvHeartbeat()
{
  int socketFd=-1;
  char* buffer=NULL;
  try{
    socketFd = socket(AF_INET, SOCK_DGRAM,0);
    if(-1 == socketFd)
    { 
      cout << "no socket" << endl;
      return NULL;
    }
    struct sockaddr_in server_info;
    memset(&server_info,0,sizeof(server_info)); // initalize server_info to 0
    server_info.sin_family=AF_INET;
    server_info.sin_port = htons(HB_PORT);             
    server_info.sin_addr.s_addr=inet_addr("0.0.0.0");

    if(-1 == bind(socketFd,(struct sockaddr*)&server_info,sizeof(struct sockaddr))){
      close(socketFd);
      cout << "bind failed" <<endl;
      return NULL;
    }

    socklen_t server_len = sizeof(struct sockaddr);
    buffer = new char[10];
    int recv_len = recvfrom(socketFd, buffer, 10,0,(struct sockaddr*)&server_info,&server_len);
    if(buffer[0]!='\x04'){
      close(socketFd);
      cout <<"recv failed(wrong flag) - "<<buffer[0] << endl;
      delete buffer;
      return NULL; // check check check
    }
  }
  catch(int exception){
    if (socketFd != -1){
      close(socketFd);
    }
    if (buffer != NULL){
      delete buffer;
    }
    return NULL;
  }

  close(socketFd);
  return buffer;
}

// hbd::heartbeatListener
// Description - heartbeat 메세지 송신대기 함수
// return - None
void hbd::heartbeatListener()
{
  char* gotData = NULL;
  heartbeat* parsedData = NULL;
  while(true){
    sleep(1);
    try{
      gotData = hbd::recvHeartbeat();
      if(gotData!=NULL){
	cout << gotData << endl;
	parsedData = parser::hbParser(gotData);
	if(parsedData!=NULL){
	  char* newhb = new char[parser::getHeartBeatPackLen(parsedData)];
          int newhbSize = packHeartBeat(newhb,parsedData);
	  hbd::sendHeartbeat(newhb, newhbSize);
	  delete newhb;
        }
      }
      else{
          cout << "recv Failed" << endl;
      }        
    }
    catch(int exception){
      cout << "Error Occured!" << endl;
    }
  }
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
