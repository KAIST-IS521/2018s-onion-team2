#ifndef	__HB_NODE_HH__
#define	__HB_NODE_HH__

#define	BYTE	unsigned char

#include <ctime>
#include <string>

using namespace std;

class hb_node {
        private:
		BYTE	Flag;		
                string  Onetimekey;
                time_t  Timestamp;
                string  IP;
                bool    Arrive;
                int     Cnt;
	public:
		hb_node(BYTE _Flag, string _Onetimekey, time_t _Timestamp, string _IP, bool _Arrive, int _Cnt);
		BYTE	getFlag();
		string getOnetimekey();
		time_t getTimestamp();
		string getIP();
		bool	getArrive();
		int	getCnt();
		void	setArrive(bool _Arrive);
};

#endif
