#include "heartbeat.hh"
using namespace std;

heartbeat::heartbeat(char* data){
  memcpy(this->OneTimeKey, data+1, 4);
}

char* heartbeat::getOneTimeKey(){
  return this->OneTimeKey;
}

void heartbeat::setHeartBeat(char* data, char* response){
  char time_stamp[TIME_T_SIZE];
  heartbeat hb = hb(data);
  response[0] = data[0];
  memcpy(response+1, hb.getOneTimeKey(), 4);
  util::time_t2byte(timestamp::getTimestampNow(), time_stamp);
  memcpy(response+5, time_stamp, 4);
}

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
