#ifndef	__LIST_CHECK_H__
#define __LIST_CHECK_H__
#include "list_node.hh"
#include <list>
#include <ctime>

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

#endif
