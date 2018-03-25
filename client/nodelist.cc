#include "nodelist.hh"
#include <iostream>
#include <list>

using namespace std;

// node::node
// Description - node 객체의 생성자 ( plain message의 datastream을 직접 파싱하여 node화 )
// return - None
node::node(char* datastream){

}

// node::node
// Description - node 객체의 생성자 ( node의 각 요소를 직접 삽입하는 형태 )
// return - None
node::node(string _GithubID, string PubKeyID, string IP){
	this->GithubID = _GithubID;
	this->PubKeyID = PubKeyID;
	this->IP = IP;
}

// node::getGithubID
// Description - node의 GithubID를 반환
// return - GithubID or Null(없을 경우)
string node::getGithubID(){
	return this->GithubID;
}

// node::getPubKeyID
// Description  - node의 PubKeyID를 반환
// return - PubKeyID or Null
string node::getPubKeyID(){
	return this->PubKeyID;
}

// node::getIP
// Description - node의 IP를 반환
// return - IP or Null
string node::getIP(){
	return this->IP;
}

// nodelist::nodelist
// Description - nodelist의 생성자 ( 첫 node를 받아서 이를 기반으로 리스트 생성 )
// return - none
nodelist::nodelist(node first_node){

}

// nodelist::searchNode
// Description - Nodelist의 node들 중 주어진 GithubID를 가진 노드의 포인터를 반환
// return - node* or Null
node* nodelist::searchNode(string GithubID){

}

// nodelist::searchNode
// Description - Nodelist의 node들 중 주어진 IP를 가진 노드의 포인터를 반환
// return - node* or Null
// node* nodelist::searchNode(string IP){

// }

// nodelist::deleteNode
// Desciption - Nodelist의 node 중 주어진 GithubID를 가진 노드의 포인터를 반환
// return - True(성공), False(실패)
bool nodelist::deleteNode(string GithubID){

}

// nodelist::deleteNode
// Desciption - Nodelist의 node 중 주어진 IP를 가진 노드의 포인터를 반환
// return - True(성공), False(실패)
// bool nodelist::deleteNode(string IP){

// }

// nodelist::getNodelistLen
// Desciption - Nodelist의 길이(=Node 수)를 반환
// return - length of Nodelist
int nodelist::getNodelistLen(){

}

// nodelist::getRandomNode
// Descripton - count 만큼의 random node들을 반환
// return - array of node , NULL
list<node*> nodelist::getRandomNode(int count){
  
}

// nodelist::getLastUpdateTime
// Desciption - list가 최근에 업데이트 된 시각을 반환
// return - timestamp
//time_t nodelist::getLastUpdateTime(); // 필요 있을까...?

// nodelist::appendNode
// Desciption - nodelist에 새 node를 추가함. 단, nodelist에 같은 GithubID나 IP가 존재하면 무시(실패 취급)
// return - True(성공), False(실패)
bool nodelist::appendNode(node append_node){

}