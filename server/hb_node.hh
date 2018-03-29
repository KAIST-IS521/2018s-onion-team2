#ifndef	__HB_NODE_HH__
#define	__HB_NODE_HH__
#include <string>

using namespace std;

class hb_node {
        private:
                string  Onetimekey;
                string  Timestamp;
                string  IP;
                bool    Arrive;
                int     Cnt;
	public:
		hb_node(string _Onetimekey, string _Timestamp, string _IP, bool _Arrive, int _Cnt);
		string getOnetimekey();
		string getTimestamp();
		string getIP();
		bool	getArrive();
		int	getCnt();
		void	setArrive(bool _Arrive);
};

#endif
