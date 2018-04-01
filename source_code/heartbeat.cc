#include "heartbeat.hh"
using namespace std;

heartbeat::heartbeat(char* data){
  memcpy(this->OneTimeKey, data+1, 4);
}

char* heartbeat::getOneTimeKey(){
  return this->OneTimeKey;
}

void heartbeat::setHeartBeat(char* data, char* response){
  // char time_stamp[TIME_T_SIZE];
  // response[0] = data[0];
  // memcpy(response+1, this->getOneTimeKey(), 4);
  // util::time_t2byte(timestamp::getTimestampNow(), time_stamp);
  // memcpy(response+5, time_stamp, 4);
}

void* hbd::recvHeartbeat(void* args)
{
  string message = "";
  char data[HB_LEN];
  struct tmd::arg_receiver *arguments = (struct tmd::arg_receiver *)args;
  string IP = arguments->IP;
  memcpy(data, arguments->buf, HB_LEN);
  delete (struct tmd::arg_receiver *)args;
  pthread_detach(pthread_self());

  if(IP == SERVER_ADDR && data[0] == '\x04'){
    char response[HB_LEN];
    heartbeat hb = heartbeat(data);
    hb.setHeartBeat(data, response);

    struct sockaddr_in saddr;
    int sockFd, saddrlen;

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
      throw "socket() failed";

    bzero((char*)&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(HB_PORT);
    if (inet_aton(SERVER_ADDR, &saddr.sin_addr) == 0)
      throw "inet_aton() failed";

    saddrlen = sizeof(saddr);
    if (sendto(sockFd, response, HB_LEN, 0, (struct sockaddr *)&saddr, (socklen_t)saddrlen) < 0)
      throw "sendto() failed";

    close(sockFd);
    return 0;
  }
}

// // hbd::SendHeartbeat
// // Description - 서버에게 heartbeat 메시지를 전달하는 함수
// // return - 전달했으면 true, 아니면 false
// bool hbd::sendHeartbeat(char* send_source, int send_size)
// {
//   char* buf;
//   int recvFd;
//   int sockFd = socket(AF_INET, SOCK_DGRAM,0);

//   if (sockFd < 0){
//     return false;
//   }
//   struct sockaddr_in sock_info, conn_info;
//   int conn_len = sizeof(conn_info);
//   bzero((char*)&sock_info, sizeof(sock_info));
//   sock_info.sin_family = AF_INET;
//   sock_info.sin_addr.s_addr = HB_SERVER_ADDR;
//   sock_info.sin_port = htons(HB_PORT);

//   if (0 > connect(sockFd,(struct sockaddr *) &sock_info,sizeof(sock_info))){
//     return false;
//   }

//   if (0 >  send(sockFd,send_source,send_size,0)){
//     return false;
//   }
//   close(sockFd);
//   return true;
// }

void hbd::heartbeat_args(userInfo user, struct tmd::arg_main* arguments){
  arguments->port = HB_PORT;
  arguments->protocol = IPPROTO_UDP;
  arguments->type = SOCK_DGRAM;
  arguments->user = user;
  arguments->func = hbd::recvHeartbeat;
}