#ifndef	__LIST_CHECK_H__
#define __LIST_CHECK_H__
#include "list_node.hh"
#include "util.hh"
#include <list>
#include <ctime>
using namespace std;

class list_check {
private:
		
public:
	list_check() {};
	list<list_node*>		onion_node;
	list<list_node*>::iterator	onionlist;
	bool	updateOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp);
	bool	appendOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp);
	bool	delOnion(string _GithubID, string _IP);
	bool	checkOnion(string _GithubID);
	list_node*	findOnion(string _GithubID, string _IP);
};

namespace lstd{
	struct arg_main {
    int protocol;
    int port;
    int type;
    void*(*func)(void*);
  };

  struct arg_data {
    string IP;
    int recvFd;
    char buf[HB_LEN];
  };

	void server_msg_args(struct lstd::arg_main* arguments);
	void* listReceiverMain(void* args);
	void* listReceiver(void* args);
}

#endif
