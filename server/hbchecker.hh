#ifndef __HBCHECKLIST_H__
#define __HBCHECKLIST_H__
#define BYTE unsigned char

#include <list>

using namespace std;

class hb_node(){
private:
 String Onetimekey;
 String Timestamp;
 String IP;
 bool Arrive;
 int Cnt;
public:
 hb_node(String _Onetimekey, String _IP, bool _bArrive, String _Timestamp);
 String getOnetimekey();
 String getTimestamp();
 String getIP();
 bool getArrive();
}

class hbChecklist() {
private:
  list<hb_node> hbchecklist;
public:
 hbchecklist(hb_node first_node);		// 날 이렇게 대한건 니가 처음이야 
 hb_node* searchNode(String IP);	// 찾아라 그놈
 hb_node* searchNode(bool Arrive);	// 찾아라 도착하지 않은놈
 int timeChecker(String Timestamp);	// 추노 대작전
 bool deleteNode(String IP);	// 졌지만 잘싸웠다.
 bool updateNode(String Onetimekey, String IP, bool Arrive, String Timestamp); // 여어 히사시부리
 bool appendNode(hb_node append_node);	// 야생의 새로운 노드가 등장했다.
 hb_node* resendClient();			// 산체로 잡아와라
}  
