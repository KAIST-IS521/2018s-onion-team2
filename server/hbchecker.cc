#include "hbchecker.hh"
#include <iostream>

using namespace std;

// hb_node::hb_node
// Description - hb_node 객체의 생성자, 최초 HB 패킷 생성
hb_node::hb_node(String _Onetimekey, String _IP, bool _bArrive, String _Timestamp) {

}

// hb_node::getOnetimekey
// Description - hb_node의 Onetimekey 반환
// return - Onetimekey or Null(없을 경우)
String hb_node::getOnetimekey() {

}

// hb_node::getTimestamp
// Description - hb_node의 Timestamp 반환
// return - Timestamp or Null(없을 경우)
String hb_node::getTimestamp() {

}

// hb_node::getIP
// Description - hb_node의 IP주소를 반환
// return - IP or Null(없을 경우)
String hb_node::getIP() {

}

// hb_node::getArrive
// Description - hb_node의 도착 여부를 반환
// return - True or False
String hb_node::getArrive() {

}


// hbchecklist::hbchecklist
// Description - hbchecklist의 생성자(첫 node를 받아서 이를 기반으로 리스트 생성)
// return - none
hbchecklist::hbchecklist(hb_node first_node) {

}

// hbchecklist::searchNode
// Description - hbchecklist의 node들 중 주어진 IP를 가진 노드의 포인터를 반환
// return - hb_node* or Null
hb_node* hbchecklist::searchNode(String IP) {

}


// hbchecklist::searchNode
// Description - hbchecklist의 node들 중 도착하지 않은 노드의 포인터를 반환
// return - hb_node* or Null
hb_node* hbchecklist::searchNode(bool Arrive) {

}


// hbchecklist::timeChecker
// Description - hb_node의 타임아웃 여부를 반환
// return - True or False
bool hbchecklist::timeChecker(String Timestamp) {

}
