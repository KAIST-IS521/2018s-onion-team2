#include "list_node.hh"

string list_node::list_node(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp) {
	GithubID = _GithubID;
	PubkeyID = _PubkeyID;
	IP	 = _IP;
	Timestamp = _Timestamp;
}

string	list_node::getGithubID() {
	return GithubID;
}

string	list_node::getPubkeyID() {
	return PubkeyID;
}

string	list_node::getIP() {
	return IP;
}

time_t	list_node::getTimestamp() {
	return Timestamp;
}

void	list_node::setTimestamp(time_t _Timestamp) {
	Timestamp = _Timestamp;
}

void	list_node::setGithubID(string _GithubID) {
	GithubID = _GithubID;
}

void	list_node::setPubkeyID(string _PubkeyID) {
	PubkeyID = _PubkeyID;
}

void	list_node::setIP(string _IP) {
	IP	= _IP;
}
