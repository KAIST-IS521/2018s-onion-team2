#ifndef __HB_CHECK_HH__
#define __HB_CHECK_HH__

#include "hb_node.hh"
#include <list>
#include <algorithm>

using namespace std;

class hb_check {
	private:
//		delay_node::iterator	delaylist;
//		sndlay_node::iterator	sndlaylist;
	public:
		list<hb_node*>			recv_node;
		list<hb_node*>::iterator	recvlist;
		hb_check() {};
		bool	updateNode(string _Onetimekey, string _IP, bool _Arrive);
		bool	appendNode(string _OTK, string _Timestamp, string _IP, bool _Arrive, int _Cnt);
		bool	delNode(string _Onetimekey, string _IP);
		hb_node*	findNode(string _Onetimekey, string _IP);
};

#endif
