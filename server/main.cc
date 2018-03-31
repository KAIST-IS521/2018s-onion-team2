#include "hb_check.hh"
#include <iostream>
#include <list>
#include <string>
#include <ctime>

using namespace std;

// 테스트용 메인
int main() {

	hb_check *a = new hb_check();
	hb_node *temp = NULL;
	list<hb_node*>::iterator iter;

	cout << (char)0x04 << endl;

	(*a).appendNode((char)0x04, "abcdabcd", time(NULL),"192.168.100.3", false, 3);
	(*a).appendNode((char)0x04, "cdecde", 1522459142, "192.168.100.4", false, 4);
	(*a).appendNode((char)0x04, "vfrvfr", time(NULL), "192.168.100.2", false, 5);

	for(iter = (*a).recv_node.begin(); iter != (*a).recv_node.end(); iter++) {
		cout << (*iter)->getIP() << endl;
	}

	(*a).delNode("abcdabcd", "192.168.100.3");

	for(iter = (*a).recv_node.begin(); iter != (*a).recv_node.end(); iter++) {
		cout << (*iter)->getFlag() << endl;
		cout << (*iter)->getIP() << ":" << (*iter)->getTimestamp() <<endl;
	}

	temp = (*a).findNode("cdecde", "192.168.100.4");
	cout << "IP :"  << temp->getIP() << temp->getArrive() << endl;

	(*a).updateNode("cdecde", "192.168.100.4", true);
	cout << "IP :" << temp->getIP() << temp->getArrive() << endl;

	(*a).updateNode("cdecde", "192.168.100.4", false);


	(*a).checkNode(time(NULL));
		
	return 0;	
}

