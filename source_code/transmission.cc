#include "transmission.hh"
#include "gpg.hh"
#include "parser.hh"
#include "message.hh"
#include <netdb.h>
#include <cstring>

// pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// tmd::tmdReceiver
// Description - tmdReceiverMain 에서 thread로 돌릴 함수, port를 계속 listen 하고 있음
// Return - 정상종료 0, 이외 음수 < 통신부 테스트 완료 >
void* tmd::tmdReceiver(void* args){
  string data = "";
  int n;
  char buf[MAX_LEN];
  struct tmd::arg_receiver *arguments = (struct tmd::arg_receiver *)args;
  int recvFd = arguments->recvFd;
  delete (struct tmd::arg_receiver *)args;
  pthread_detach(pthread_self());

  while ((n = read(recvFd, buf, MAX_LEN)) > 0) {
    data += buf;
  }
  string passphrase = user.getPassphrase();
  char* stream = gpg::decBytestream((char*)data.c_str(), &passphrase);
  if(stream[0] == '\x00'){
    encMessage* msg = parser::encMessageParser(stream);
    struct tmd::arg_data* list_update_arguments = new struct tmd::arg_data();
    tmd::data_args(msg->getNextIP(), (char*)(msg->getEncData().c_str()), list_update_arguments);
    pthread_t th_list_update;
    pthread_create(&th_list_update, NULL, tmd::tmdSender, (void*)list_update_arguments);
    msg->getNextIP();
    delete msg;
  } else if(stream[0] == '\x01') {
    message* msg = parser::messageParser(stream);
    pthread_mutex_lock(&m_user);
    user.addMessage(*msg);
    pthread_mutex_unlock(&m_user);
    delete msg;
  } else if(stream[0] == '\x02'){
    node* new_node = parser::nodeParser(stream);
    pthread_mutex_lock(&m_node_list);
    node_list.appendNode(new_node);
    pthread_mutex_unlock(&m_node_list);
  }
  delete stream;
  close(recvFd);
  return NULL;
}

void* tmd::tmdReceiverMain(void* args){
  int n, sockFd, caddrlen, recvFd;
  struct sockaddr_in saddr, caddr;
  struct tmd::arg_receiver* arg_recv;
  struct hostent *h;

  struct tmd::arg_main* arguments = (struct tmd::arg_main*)args;
  int port = arguments->port;
  int protocol = arguments->protocol;
  int type = arguments->type;
  void*(*func)(void*) = arguments->func;

  delete (struct tmd::arg_main*)args;

  if ((sockFd = socket(AF_INET, type, protocol)) < 0)
    throw "socket() failed.";

  bzero((char *)&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons(port);
  
  if (bind(sockFd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    throw "bind() failed.";

  if(protocol == IPPROTO_TCP){
    if (listen(sockFd, MAX_QUEUE) < 0)
      throw "listen() failed.";

    while (1) {
      caddrlen = sizeof(caddr);
      arg_recv = new struct tmd::arg_receiver();
      if ((arg_recv->recvFd = accept(sockFd, (struct sockaddr *)&caddr, (socklen_t*)&caddrlen)) < 0){
        delete arg_recv;
        continue;
      }
      h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, sizeof(caddr.sin_addr.s_addr), AF_INET);
      arg_recv->IP = inet_ntoa(*(struct in_addr *)&caddr.sin_addr);
      pthread_t tid;
      pthread_create(&tid, NULL, func, (void *)arg_recv);
    }
  } else {
    while(1){
      caddrlen = sizeof(caddr);
      arg_recv = new struct tmd::arg_receiver();
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

void tmd::msg_args(struct tmd::arg_main* arguments){
  arguments->port = MESSAGE_PORT;
  arguments->protocol = IPPROTO_TCP;
  arguments->type = SOCK_STREAM;
  arguments->func = tmd::tmdReceiver;
}

void tmd::data_args(string IP, char* data, struct tmd::arg_data* list_update_arguments){
  list_update_arguments->IP = IP;
  list_update_arguments->data = new char[MAX_LEN];
  memcpy(list_update_arguments->data, data, MAX_LEN);
  list_update_arguments->length = MAX_LEN;
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
  string IP = arguments->IP;
  char* data = new char[length];
  memcpy(data, arguments->data, length);
  
  delete arguments->data;
  delete arguments;

  // pthread_detach(pthread_self());
  cout << "Message start" << endl;
  try{
    if ((cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
      delete data;
      throw "socket() failed.";
    }

    if ((h = gethostbyname(IP.c_str())) == NULL){
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
  } catch (string e){
    cout << "Unreachable: " + e << endl;
    cout << "Terminating the program" << endl;
    close(cfd);
    exit(3);
  }

  write(cfd, data, length);
  close(cfd);

  cout << "Message sent" << endl;

  delete data;

  return NULL;
}