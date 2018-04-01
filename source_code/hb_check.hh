#ifndef __HB_CHECK_HH__
#define __HB_CHECK_HH__

#include "hb_node.hh"
#include <ctime>
#include <list>

using namespace std;

class hb_check {
private:
//		delay_node::iterator	delaylist;
//		sndlay_node::iterator	sndlaylist;
public:
	list<hb_node*>			recv_node;
	list<hb_node*>::iterator	recvlist;
	list<hb_node*>			resend_node;
	list<hb_node*>::iterator	resendlist;
	hb_check() {};
	bool	updateNode(string _Onetimekey, string _IP, bool _Arrive);
	bool	appendNode(BYTE _Flag, string _OTK, time_t _Timestamp, string _IP, bool _Arrive, int _Cnt);
	bool	delNode(string _Onetimekey, string _IP);
	bool	checkNode(time_t _Timestamp);
//		bool	resendNode(hb_node* _rndNode);
	hb_node*	findNode(string _Onetimekey, string _IP);
};

#endif
