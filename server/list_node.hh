#ifndef __LIST_NODE_HH__
#define __LIST_NODE_HH__

#define BYTE	unsigned char

#include <string>

using namespace std;

class list_node {
	private:
		string GithubID;
		string PubkeyID;
		string IP;
		time_t Timestamp;
	public:
		list_node(string _GithubID, string PubkeyID, string _IP, time_t _Timestamp);
		string	getGithubID();
		string	getPubkeyID();
		string	getIP();
		time_t	getTimestamp();
		void	setTimestamp(time_t _Timestamp);
		void	setGithubID(string _GithubID);
		void	setPubkeyID(string _PubkeyID);
		void	setIP(string _IP);
};

#endif
