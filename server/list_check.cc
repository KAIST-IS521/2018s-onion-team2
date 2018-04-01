#include "list_check.hh"
#include <cstring>

bool list_check::updateOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp) {
	string __GithubID = _GithubID;
	string __IP	  = _IP;
	time_t __Timestamp = _Timestamp;

	list_node* fndTmp = findOnion(__GithubID, __IP);

	(*fndTmp).setTimestamp(__Timestamp);

	return true;
}

bool list_check::appendOnion(string _GithubID, string _PubkeyID, string _IP, time_t _Timestamp) {
	if ((_GithubID).length() > 40)
		return false;
	string __GithubID = _GithubID;
	string __PubkeyID = _PubkeyID;
	string __IP = _IP;
	time_t __Timestamp = __Timestamp;

	onion_node.push_back(new list_node(__GithubID, __PubkeyID, __IP, time(NULL)));

	return true;
}

bool list_check::delOnion(string _GithubID, string _IP) {
	string __GithubID = _GithubID;
	string __IP = _IP;

	for(onionlist = onion_node.begin(); onionlist != onion_node.end(); ++onionlist) {
		if((*onionlist)->getGithubID() == __GithubID && (*onionlist)->getIP() == __IP) {
			delete(*onionlist);
			onionlist = onion_node.erase(onionlist++);
		}
		else
			++onionlist;
	}

	return true;
}

bool list_check::checkOnion(string _GithubID) {


	return true;
}

list_node* list_check::findOnion(string _GithubID, string _IP) {
	string __GithubID = _GithubID;
	string __IP	  = _IP;
	
	for(onionlist = onion_node.begin(); onionlist != onion_node.end(); ++onionlist) {
		if((*onionlist)->getGithubID() == __GithubID && (*onionlist)->getIP() == __IP) {
			return (*onionlist);
		}
	}
	return NULL;
}
