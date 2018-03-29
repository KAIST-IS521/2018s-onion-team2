#include "hb_node.hh"

using namespace std;

hb_node::hb_node(string _Onetimekey, string _Timestamp, string _IP, bool _Arrive, int _Cnt) {
	Onetimekey	= _Onetimekey;
	Timestamp	= _Timestamp;
	IP		= _IP;
	Arrive		= _Arrive;
	Cnt		= _Cnt;
}

string hb_node::getOnetimekey() {
	return Onetimekey;
}

string hb_node::getTimestamp() {
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
