#include "transmission.hh"
#include "list_checker.hh"
#include <netdb.h>
#include <cstring>

// pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// tmd::tmdReceiver
// Description - tmdReceiverMain 에서 thread로 돌릴 함수, port를 계속 listen 하고 있음
// Return - 정상종료 0, 이외 음수 < 통신부 테스트 완료 >
void* tmd::tmdReceiver(void* args){
  string message = "";
  int n;
  char buf[MAX_LEN];
  struct tmd::arg_receiver *arguments = (struct tmd::arg_receiver *)args;
  int recvFd = arguments->recvFd;
  userInfo user = arguments->user;
  delete (struct tmd::arg_receiver *)args;
  pthread_detach(pthread_self());

  while ((n = read(recvFd, buf, MAX_LEN)) > 0) {
    // write(recvFd, buf, n);
    message += buf;
  }

  close(recvFd);

  cout << user.getGithubID() << endl;
  cout << message << endl;

  // buf = gpg::decBytestream(buf,passphrase);
  // switch(buf[0]){
  //   // 0x04(heartbeat) 여기서 발견되면 안됨.
  //   // MUTEX 잘 써야 함
  //   //pthread_mutex_lock(&m);
  //   //pthread_mutex_unlock(&m);
  //   case '\x00':
  //     // 평문 : message 객체로 만들고, storage에 저장
  //     break;

  //   case '\x01':
  //     // 암호문 : 길이 및 메세지 따서 해당 서버로 재송신

  //     break;

  //   case '\x02':
  //     // 리스트 업데이트 : 프로토콜에 맞게 파싱하여 리스트에 추가/삭제

  //     break;
  //   default:
  //     // fail : 무시
  //     break;
  // }
  return NULL;
}

void* tmd::tmdReceiverMain(void* args){
  int n, sockFd, caddrlen, recvFd;
  struct sockaddr_in saddr, caddr;
  struct tmd::arg_receiver* arg_recv;
  struct hostent *h;

  struct tmd::arg_main* arguments = (struct tmd::arg_main*)args;
  userInfo user = arguments->user;
  int port = arguments->port;
  int protocol = arguments->protocol;
  int type = arguments->type;
  void*(*func)(void*) = arguments->func;

  delete (struct tmd::arg_main*)args;

  cout << "socket creating ..." << endl;
  if ((sockFd = socket(AF_INET, type, protocol)) < 0)
    throw "socket() failed.";

  bzero((char *)&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons(port);
  
  cout << "binding ..." << endl;
  if (bind(sockFd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    throw "bind() failed.";

  if(protocol == IPPROTO_TCP){
    cout << "listening ..." << endl;
    if (listen(sockFd, MAX_QUEUE) < 0)
      throw "listen() failed.";

    while (1) {
      caddrlen = sizeof(caddr);
      arg_recv = new struct tmd::arg_receiver();
      arg_recv->user = user;
      cout << "Waiting connections ..." << endl;
      if ((arg_recv->recvFd = accept(sockFd, (struct sockaddr *)&caddr, (socklen_t*)&caddrlen)) < 0){
        delete arg_recv;
        continue;
      }
      h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, sizeof(caddr.sin_addr.s_addr), AF_INET);
      arg_recv->IP = inet_ntoa(*(struct in_addr *)&caddr.sin_addr);
      cout << "Creationg Thread" << endl;
      pthread_t tid;
      pthread_create(&tid, NULL, func, (void *)arg_recv);
    }
  } else {
    while(1){
      caddrlen = sizeof(caddr);
      arg_recv = new struct tmd::arg_receiver();
      arg_recv->user = user;
      cout << "Waiting connections ..." << endl;
      if ((n = recvfrom(sockFd, arg_recv->buf, HB_LEN, 0, (struct sockaddr *)&caddr, (socklen_t*)&caddrlen)) < 0){
        delete arg_recv;
        continue;
      }
      h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, sizeof(caddr.sin_addr.s_addr), AF_INET);
      arg_recv->IP = inet_ntoa(*(struct in_addr *)&caddr.sin_addr);
      pthread_t tid;
      pthread_create(&tid, NULL, func, (void *)arg_recv);
    }
  }

  return NULL;
}

void tmd::msg_args(userInfo user, struct tmd::arg_main* arguments){
  arguments->port = MESSAGE_PORT;
  arguments->protocol = IPPROTO_TCP;
  arguments->type = SOCK_STREAM;
  arguments->user = user;
  arguments->func = tmd::tmdReceiver;
}

// // tmd::tmdPathSelecter
// // Description - 타 클라이언트로 메세지 전송시 Path를 결정. nodes 만큼의 클라이언트를 거치도록 만들어줌
// // Return - IP 배열  or Null(실패)
// list<node*> tmd::tmdPathSelecter(int nodes){
//   return nodelist::getRandomNode(nodes-1);
// }

// // tmd::tmdPackPacket
// // Desctiption - 평문 char stream을 송신자와 Path 순서 대로 암호화를 한다.
// // Return - 암호화된 char stream
// char* tmd::tmdPackPacket(node* sender, node* reciver, char* plain){
//   list<node*> pathlist = tmd::tmdPathSelecter(3);
//   if(pathlist.size() < 3){
//     return NULL;
//   }
//   char* encPr = gpg::encBytestream(plain,reciver->node::getPubKeyID());
  
//   // pathlist : reciver -> B -> C
//   // in real : C -> B -> reciver 
//   pathlist.insert(pathlist.begin(),reciver);

//   // encPr = Erec(Prec)
//   // structure : EC(EB(encPr,Erec)EB)
//   std::list<node*> iterator i = pathlist.begin();
//   while (i!=pathlist.end()){
//     encPr = gpg::encBytestream(parser::packEncMessage(encPr,*(i)->getIP()), *(i+1)->getPubKeyID());
//     i++;
//   }

//   return encPr;
// }

void* tmd::tmdSender(void* args){
  int n, cfd;
  struct hostent *h;
  struct sockaddr_in saddr;
  
  struct tmd::arg_data* arguments = (struct tmd::arg_data*) args;
  int length = arguments->length;
  char* data = new char[length];
  memcpy(data, arguments->data, length);
  
  delete arguments->data;
  delete arguments;

  pthread_detach(pthread_self());

  if ((cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
    delete data;
    throw "socket() failed.";
  }

  if ((h = gethostbyname(SERVER_ADDR)) == NULL){
    delete data;
    throw "gethostbyname() failed"; 
  }

  bzero((char *)&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  bcopy((char *)h->h_addr, (char *)&saddr.sin_addr.s_addr, h->h_length);
  saddr.sin_port = htons(MESSAGE_PORT);

  if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
    delete data;
    throw "connect() failed.";
  }

  write(cfd, data, length);
  close(cfd);

  delete data;

  return NULL;
} 
