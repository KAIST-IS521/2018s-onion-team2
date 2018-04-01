#include "hb_node.hh"

using namespace std;

hb_node::hb_node(BYTE _Flag, string _Onetimekey, time_t _Timestamp, string _IP, bool _Arrive, int _Cnt) {
	Flag		= _Flag;
	Onetimekey	= _Onetimekey;
	Timestamp	= _Timestamp;
	IP		= _IP;
	/* FOR MANAGEMENT */
	Arrive		= _Arrive;
	Cnt		= _Cnt;
}

BYTE	hb_node::getFlag() {
	return Flag;
}

string hb_node::getOnetimekey() {
	return Onetimekey;
}

time_t hb_node::getTimestamp() {
	return Timestamp;
}

string hb_node::getIP() {
	return IP;
}

bool hb_node::getArrive() {
	return Arrive;
}

int hb_node::getCnt() {
	return Cnt;
}

void hb_node::setArrive(bool _Arrive) {
	Arrive = _Arrive;	
}
