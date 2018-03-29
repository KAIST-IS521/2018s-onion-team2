#include <iostream>
#include <list>
#include "hb_check.hh"

using namespace std;


// 테스트용 메인
int main() {

	hb_check *a = new hb_check();
	hb_node *temp = NULL;
	list<hb_node*>::iterator iter;

	(*a).appendNode("abcdabcd", "123451234","192.168.100.3", false, 3);
	(*a).appendNode("cdecde", "56785678", "192.168.100.4", false, 4);
	(*a).appendNode("vfrvfr", "908908", "192.168.100.2", false, 5);

	for(iter = (*a).recv_node.begin(); iter != (*a).recv_node.end(); iter++) {
		cout << (*iter)->getIP() << endl;
	}

	(*a).delNode("abcdabcd", "192.168.100.3");

	for(iter = (*a).recv_node.begin(); iter != (*a).recv_node.end(); iter++) {
		cout << (*iter)->getIP() << endl;
	}

	temp = (*a).findNode("cdecde", "192.168.100.4");
	cout << "IP :"  << temp->getIP() << temp->getArrive() << endl;

	(*a).updateNode("cdecde", "192.168.100.4", true);
	cout << "IP :" << temp->getIP() << temp->getArrive() << endl;
		
	return 0;	
}

