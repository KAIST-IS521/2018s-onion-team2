#include "transmission.hh"
#include <iostream>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// tmd::tmdReciver
// Description - tmdReciverMain 에서 thread로 돌릴 함수, port를 계속 listen 하고 있음
// Return - 정상종료 0, 이외 음수 < 통신부 테스트 완료 >
void* tmd::tmdReciver(void* recvFd){
  char* buf;
  char* tempBuf = new char[1024];
  int curBufSize=0;
  int streamSize=1024;
  int recvFd = *(int*)_recvFd;
  pthread_detach(pthread_self());
  try{
    while(read(recvFd,tempBuf,1024)){
      if(curBufSize==0){
        buf = new char[1024];
        strncpy(buf,tempBuf,1024);
        bzero(tempBuf,1024);
        curBufSize = 1024;
      }
      else{
        char* newBuf = new char[curBufSize+1024];
        bzero(newBuf, curBufSize+1024);
        strncpy(newBuf,buf,curBufSize);
        strncat(newBuf,tempBuf,1024);
        bzero(tempBuf,1024);
        curBufSize += 1024;
        delete[] buf;
        buf = newBuf;
      }
    }
  }
  catch(int exceptionCode){
  }
 // return buf;
 // processing recived packet

  buf = tmdReciver(recvFd);
  // decypt buf by pubkey
 string passphrase('asdfasdfa'); // example
 buf = gpg::decBytestream(buf,passphrase);
 switch(buf[0]){
    // 0x04(heartbeat) 여기서 발견되면 안됨.
    // MUTEX 잘 써야 함
    //pthread_mutex_lock(&m);
    //pthread_mutex_unlock(&m);
    case '\x00':
      // 평문 : message 객체로 만들고, storage에 저장
      break;

    case '\x01':
      // 암호문 : 길이 및 메세지 따서 해당 서버로 재송신

      break;

    case '\x02':
      // 리스트 업데이트 : 프로토콜에 맞게 파싱하여 리스트에 추가/삭제

      break;
    default:
      // fail : 무시
      break;
  }
  return 0;
}

// tmd::tmdReciverMain
// Description - 지속적으로 tmdReciver 함수를 돌림. tmdReciver에서 반환한 char STREAM을 처리하고 계속 돌아야함.
// Return - 0(정상 종료), -1(이상 종료) // 구현하기 힘들면 void로 변경해도 무방. < 통신부 테스트 완료 >
int tmd::tmdReciverMain(){
  char* buf;
  int recvFd;
  int sockFd = socket(AF_INET, SOCK_STREAM,0);
  pthread_t tid[MAX_THREAD];
  if (sockFd < 0){
    return -1;
  }
  struct sockaddr_in sock_info, conn_info;
  int conn_len = sizeof(conn_info);
  bzero((char*)&sock_info, sizeof(sock_info));
  sock_info.sin_family = AF_INET;
  sock_info.sin_addr.s_addr = INADDR_ANY;
  sock_info.sin_port = htons(MESSAGE_PORT);

  if (0 > bind(sockFd,(struct sockaddr *) &sock_info,sizeof(sock_info))){
    return -2;
  }

  if (0 > listen(sockFd,10)){
    return -3;
  }

  while(true){
    for(int i=0;i<MAX_THREAD;i++){
      recvFd = accept(sockFd, (struct sockaddr*)&conn_info, (socklen_t*)&conn_len);
      cout << recvFd << endl;
      if(recvFd<0){
        return -4;
      }
      pthread_create(&tid[i],NULL,tmdReciver,(void **)&recvFd);
    }
  }
  return 0;

}

// tmd::tmdPathSelecter
// Description - 타 클라이언트로 메세지 전송시 Path를 결정. nodes 만큼의 클라이언트를 거치도록 만들어줌
// Return - IP 배열  or Null(실패)
list<node*> tmd::tmdPathSelecter(int nodes){
  return nodelist::getRandomNode(nodes-1);
}

// tmd::tmdPackPacket
// Desctiption - 평문 char stream을 송신자와 Path 순서 대로 암호화를 한다.
// Return - 암호화된 char stream
char* tmd::tmdPackPacket(node* sender, node* reciver, char* plain){
  list<node*> pathlist = tmd::tmdPathSelecter(3);
  if(pathlist.size() < 3){
    return NULL;
  }
  char* encPr = gpg::encBytestream(plain,reciver->node::getPubKeyID());
  
  // pathlist : reciver -> B -> C
  // in real : C -> B -> reciver 
  pathlist.insert(pathlist.begin(),reciver);

  // encPr = Erec(Prec)
  // structure : EC(EB(encPr,Erec)EB)
  std::list<node*> iterator i = pathlist.begin();
  while (i!=pathlist.end()){
    encPr = gpg::encBytestream(parser::packEncMessage(encPr,*(i)->getIP()), *(i+1)->getPubKeyID());
    i++;
  }

  return encPr;
}

// tmd::tmdSender
// Description - char stream을 특정 IP로 전송함.
// Return - True(성공), False(실패)      <test 완료>
bool tmd::tmdSender(string IP, char* scheme, int scheme_len){
  char* buf;
  int recvFd;
  int sockFd = socket(AF_INET, SOCK_STREAM,0);

  if (sockFd < 0){
    return -1;
  }
  struct sockaddr_in sock_info, conn_info;
  int conn_len = sizeof(conn_info);
  bzero((char*)&sock_info, sizeof(sock_info));
  sock_info.sin_family = AF_INET;
  sock_info.sin_addr.s_addr = inet_addr(IP.c_str());
  sock_info.sin_port = htons(MESSAGE_PORT);

  if (0 > connect(sockFd,(struct sockaddr *) &sock_info,sizeof(sock_info))){
    return -2;
  }

  if (0 >  send(sockFd,scheme,scheme_len,0)){
    return -3;
  }
  close(sockFd);
  return 0;
}

