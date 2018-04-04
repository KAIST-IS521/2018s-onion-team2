#include "list_check.hh"
#include "parser.hh"
#include "gpg.hh"
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

  bzero(buf, MAX_LEN);
  n = read(recvFd, buf, MAX_LEN);
  if(buf[0] == '\x02'){
    node* new_node = parser::nodeParser(buf);
    pthread_mutex_lock(&m_node_list);
    node_list.appendNode(new_node);
    string pubKeyID = new_node->getPubKeyID();
    gpg::recvPubKey(&pubKeyID);
    vector<string>* id_list = node_list.getGithubIDList();
    for(std::vector<string>::iterator it = id_list->begin() ; it != id_list->end(); ++it){
      node* _node = node_list.searchNode(*it, 0);
      char stream[MAX_LEN];
      int length = parser::packNode(stream, _node, SIGN_IN);
      char* encStream =  gpg::encBytestream(stream, &pubKeyID, length);
      struct tmd::arg_data* list_update_arguments = new struct tmd::arg_data();
      tmd::data_args(_node->getIP(), encStream, list_update_arguments);
      delete encStream;
      pthread_t th_list_update;
      pthread_create(&th_list_update, NULL, tmd::tmdSender, (void*)list_update_arguments);
    }
    pthread_mutex_unlock(&m_node_list);
    delete id_list;
  }

  close(recvFd);
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
      arg_recv = new struct lstd::arg_data();
      if ((arg_recv->recvFd = accept(sockFd, (struct sockaddr *)&caddr, (socklen_t*)&caddrlen)) < 0){
        delete arg_recv;
        continue;
      }
      h = gethostbyaddr((const char *)&caddr.sin_addr.s_addr, sizeof(caddr.sin_addr.s_addr), AF_INET);
      arg_recv->IP = inet_ntoa(*(struct in_addr *)&caddr.sin_addr);
      pthread_t tid;
      pthread_create(&tid, NULL, func, (void *)arg_recv);
      pthread_join(tid, NULL);
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