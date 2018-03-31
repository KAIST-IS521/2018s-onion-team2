#include "hb_check.hh"
#include <iostream>
#include <ctime>


using namespace std;

bool hb_check::updateNode(string _Onetimekey, string _IP, bool _Arrive) {
//        string __OTK    = _Onetimekey;
	string __OTK	= _Onetimekey;
        string __IP     = _IP;
	bool __Arrive	= _Arrive;

        for(recvlist = recv_node.begin(); recvlist != recv_node.end(); ++recvlist) {
                if((*recvlist)->getIP() == __IP && (*recvlist)->getOnetimekey() == __OTK) {
			(*recvlist)->setArrive(__Arrive);
//                      cout << __IP << endl;
                }
        }
	return true;
}

bool hb_check::appendNode(BYTE _Flag, string _OTK, time_t _Timestamp, string _IP, bool _Arrive, int _Cnt) {
	BYTE   __Flag	= _Flag;
	string __OTK	= _OTK;
	time_t __Timestamp = _Timestamp;
	string __IP	= _IP;
	bool __Arrive	= _Arrive;
	int __Cnt	= _Cnt;

	recv_node.push_back(new hb_node(__Flag, __OTK, __Timestamp, __IP, __Arrive, __Cnt));

	return true;
}

bool hb_check::delNode(string _Onetimekey, string _IP) {
	string __OTK	= _Onetimekey;
	string __IP	= _IP;

	for(recvlist = recv_node.begin(); recvlist != recv_node.end(); ++recvlist) {
		if((*recvlist)->getIP() == __IP && (*recvlist)->getOnetimekey() == __OTK) {
			delete(*recvlist);
			recvlist = recv_node.erase(recvlist++);	
//			cout << __IP << endl;
		}
		else
			++recvlist;
	}

	return true;
}

hb_node*  hb_check::findNode(string _Onetimekey, string _IP) {
        string __OTK    = _Onetimekey;
        string __IP     = _IP;

        for(recvlist = recv_node.begin(); recvlist != recv_node.end(); ++recvlist) {
//                if((*recvlist)->getIP() == __IP && (*recvlist)->getOnetimekey() == __OTK) {
		if((*recvlist)->getIP() == __IP) {
                        return (*recvlist);
//                      cout << __IP << endl;
                }
        }
	return NULL;
}

bool	hb_check::checkNode(time_t _Timestamp) {
	time_t currentTime = time(NULL);
	time_t __Timestamp = _Timestamp;

	for(recvlist = recv_node.begin(); recvlist != recv_node.end(); ++recvlist) {
		if((*recvlist)->getArrive() == false && (currentTime - (*recvlist)->getTimestamp()) >= 5) {
			cout << "Test" << endl;
		}
	}
	return false;
}

/*bool	hb_check::resendNode(hb_node* _rndNode) {
//	*hb_node __rndNode = _rndNode;

	return true;
}*/

