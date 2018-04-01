#include "list_check.hh"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <netdb.h>

void lstd::server_msg_args(struct lstd::arg_main* arguments){
  arguments->port = MESSAGE_PORT;
  arguments->protocol = IPPROTO_TCP;
  arguments->type = SOCK_STREAM;
  arguments->func = lstd::listReceiver;
}

void* lstd::listReceiver(void* args){
  string message = "";
  char buf[MAX_LEN];
  int n;
  struct lstd::arg_data *arguments = (struct lstd::arg_data *)args;
  int recvFd = arguments->recvFd;
  string IP = arguments->IP;
  delete arguments;
  pthread_detach(pthread_self());

  // struct packet pkt;
  
  n = read(recvFd, buf, MAX_LEN);
  switch(recvFd){
    case '\x02':
      
  }


  close(recvFd);
  // while(pkt.getPkt(buf))
  //   for (int i = 0; i < MAX_LEN; ++i)
  //     cout << buf[i];
  // cout << endl;
  // cout << message.length() << endl;

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

void* lstd::listReceiverMain(void* args){
	int n, sockFd, caddrlen, recvFd;
  struct sockaddr_in saddr, caddr;
  struct lstd::arg_data* arg_recv;
  struct hostent *h;

  struct lstd::arg_main* arguments = (struct lstd::arg_main*)args;
  int port = arguments->port;
  int protocol = arguments->protocol;
  int type = arguments->type;
  void*(*func)(void*) = arguments->func;

  delete (struct lstd::arg_main*)args;

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
      arg_recv = new struct lstd::arg_data();
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
      arg_recv = new struct lstd::arg_data();
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

// bool list_check::updateOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp) {
// 	string __GithubID = _GithubID;
// 	string __IP	  = _IP;
// 	time_t __Timestamp = _Timestamp;

// 	list_node* fndTmp = findOnion(__GithubID, __IP);

// 	(*fndTmp).setTimestamp(__Timestamp);

// 	return true;
// }

// bool list_check::appendOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp) {
// 	if ((_GithubID).length() > 40)
// 		return false;
// 	string __GithubID = _GithubID;
// 	string __PubkeyID = _PubkeyID;
// 	string __IP = _IP;
// 	time_t __Timestamp = __Timestamp;

// 	onion_node.push_back(new list_node(__GithubID, __PubkeyID, __IP, time(NULL)));

// 	return true;
// }

// bool list_check::delOnion(string _GithubID, string _IP) {
// 	string __GithubID = _GithubID;
// 	string __IP = _IP;

// 	for(onionlist = onion_node.begin(); onionlist != onion_node.end(); ++onionlist) {
// 		if((*onionlist)->getGithubID() == __GithubID && (*onionlist)->getIP() == __IP) {
// 			delete(*onionlist);
// 			onionlist = onion_node.erase(onionlist++);
// 		}
// 		else
// 			++onionlist;
// 	}

// 	return true;
// }

// bool list_check::checkOnion(string _GithubID) {


// 	return true;
// }

// list_node* list_check::findOnion(string _GithubID, string _IP) {
// 	string __GithubID = _GithubID;
// 	string __IP	  = _IP;
	
// 	for(onionlist = onion_node.begin(); onionlist != onion_node.end(); ++onionlist) {
// 		if((*onionlist)->getGithubID() == __GithubID && (*onionlist)->getIP() == __IP) {
// 			return (*onionlist);
// 		}
// 	}
// 	return NULL;
// }
