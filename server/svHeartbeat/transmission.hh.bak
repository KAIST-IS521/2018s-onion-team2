#ifndef __TRANSMISSION_HH__
#define	__TRANSMISSION_HH__

#define	MESSAGE_PORT		56827
#define MAX_THREAD		10
#define	CURRENTBUFSIZE		1024
#define	MAX_PATH		3
#include <iostream>
#include <list>
using namespace std;

class tmd{
	list<node*> 	tmdPathSelector();
	char*		tmdReciver();
	int		tmdReciverMain();
	char		tmdPackPacket(node* sender, node* receiver, BYTE* plain);
	bool		tmdSender(string IP, char* scheme);
};

#endif
