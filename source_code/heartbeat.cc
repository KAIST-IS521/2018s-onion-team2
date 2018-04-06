#include "heartbeat.hh"
#include "timestamp.hh"
using namespace std;

heartbeat::heartbeat(char* data){
  memcpy(this->OneTimeKey, data, 4);
}

char* heartbeat::getOneTimeKey(){
  return this->OneTimeKey;
}

void heartbeat::setHeartBeat(char* data, char* response){
  response[0] = data[0];
  memcpy(response+1, this->getOneTimeKey(), 4);
  char* time_stamp = timestamp::timestamp2byte(timestamp::getTimestampNow());
  memcpy(response+5, time_stamp, 4);
  delete time_stamp;
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
    heartbeat hb = heartbeat(data+1);
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

void hbd::heartbeat_args(struct tmd::arg_main* arguments){
  arguments->port = HB_PORT;
  arguments->protocol = IPPROTO_UDP;
  arguments->type = SOCK_DGRAM;
  arguments->func = hbd::recvHeartbeat;
}
