#include "transmission.hh"
#include "parser.hh"
#include "msg_ui.hh"
#include <sys/types.h>
#include <signal.h>


// tmd::tmdReceiver
// Description - tmdReceiverMain 에서 thread로 돌릴 함수, port를 계속 listen 하고 있음
// Return - 정상종료 0, 이외 음수 < 통신부 테스트 완료 >
void* tmd::tmdReceiver(void* args){
  string data = "";
  int n;
  char buf[MAX_LEN];
  struct tmd::arg_receiver *arguments = (struct tmd::arg_receiver *)args;
  int recvFd = arguments->recvFd;
  string you = arguments->you;
  delete (struct tmd::arg_receiver *)args;
  pthread_detach(pthread_self());
  while ((n = read(recvFd, buf, MAX_LEN)) > 0) {
    data += buf;
  }
  string passphrase = user.getPassphrase();
  char* stream = gpg::decBytestream((char*)data.c_str(), &passphrase);
  if(stream[0] == '\x00'){
    encMessage* msg = parser::encMessageParser(stream);
    struct tmd::arg_data* msg_argument = new struct tmd::arg_data();
    tmd::data_args(msg->getNextIP(), (char*)(msg->getEncData().c_str()), msg_argument);
    pthread_t th_forward;
    pthread_create(&th_forward, NULL, tmd::tmdSender, (void*)msg_argument);

    delete msg;
  } else if(stream[0] == '\x01') {
    message msg;
    parser::messageParser(stream,&msg);
    pthread_mutex_lock(&m_user);
    user.addMessage(msg);
    pthread_mutex_unlock(&m_user);
    msg_ui::refresh_messages(user.getGithubID());
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
  string you = arguments->you;
  void*(*func)(void*) = arguments->func;

  delete arguments;
  pthread_detach(pthread_self());

  try{
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
    }
  } catch (char const* e){
    cout << string(e) << endl;
    cout << "Terminating the program ..." << endl;
    close(sockFd);
    exit(2);
  }

  return NULL;
}

void tmd::msg_args(struct tmd::arg_main* arguments,string hostid){
  arguments->port = MESSAGE_PORT;
  arguments->protocol = IPPROTO_TCP;
  arguments->type = SOCK_STREAM;
  arguments->func = tmd::tmdReceiver;
  arguments->you = hostid;
}

void tmd::data_args(string IP, char* data, struct tmd::arg_data* list_update_arguments){
  list_update_arguments->IP = IP;
  list_update_arguments->data = new char[MAX_LEN];
  memcpy(list_update_arguments->data, data, MAX_LEN);
  list_update_arguments->length = MAX_LEN;
}

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

  pthread_detach(pthread_self());
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
  } catch (char const* e){
    cout << "Unreachable: " + string(e) << endl;
    cout << "Terminating the program ..." << endl;
    close(cfd);
    exit(2);
  }

  write(cfd, data, length);
  close(cfd);
  delete data;

  return NULL;
}
