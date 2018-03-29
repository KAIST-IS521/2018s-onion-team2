#include "nodelist.hh"

using namespace std;
// node::node
// Description - node 객체의 생성자 ( node의 각 요소를 직접 삽입하는 형태 )
// return - None
node::node(string _GithubID, String PubKeyID, String IP){
  this->GithubID = _GithubID;
  this->PubKeyID = PubKeyID;
  this->IP = IP;

  delete _GithubID;
  delete PubKeyID;
  delete IP;
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
nodelist::nodelist(node* first_node){
  this->nodelist = new list<node*>(first_node);
}

// nodelist::searchNode
// Description - Nodelist의 node들 중 주어진 GithubID를 가진 노드의 포인터를 반환
// return - node* or Null
node* nodelist::searchNode(string GithubID){
  for(std::list<node*>::iterator pick = this->nodelist.begin();pick!=this->nodelist.end();pick++){
    if((*pick->getGithubID()).compare(GithubID)==0){
      return *pick;
    }
  }
  return NULL;
}

// nodelist::searchNode
// Description - Nodelist의 node들 중 주어진 IP를 가진 노드의 포인터를 반환
// return - node* or Null
node* nodelist::searchNode(string IP){
  for(std::list<node*>::iterator pick = this->nodelist.begin();pick!=this->nodelist.end();pick++){
    if((*pick->getIP()).compare(IP)==0){
      return *pick;
    }
  }
  return NULL;
}

// nodelist::deleteNode
// Desciption - Nodelist의 node 중 주어진 GithubID를 가진 노드의 포인터를 반환
// return - True(성공), False(실패)
bool nodelist::deleteNode(string GithubID){
  for(std::list<node*>::iterator pick = this->nodelist.begin();pick!=this->nodelist.end();pick++){
    if((*pick->getGithubID()).compare(GithubID)==0){
      this->nodelist.erase(*pick);
      return true;
    }
  }
  return false;
}

// nodelist::deleteNode
// Desciption - Nodelist의 node 중 주어진 IP를 가진 노드의 포인터를 반환
// return - True(성공), False(실패)
bool nodelist::deleteNode(string IP){
  for(std::list<node*>::iterator pick = this->nodelist.begin();pick!=this->nodelist.end();pick++){
    if((*pick->getIP()).compare(IP)==0){
      this->nodelist.erase(*pick);
      return true;
    }
  }
  return false;
}

// nodelist::getNodelistLen
// Desciption - Nodelist의 길이(=Node 수)를 반환
// return - length of Nodelist
int nodelist::getNodelistLen(){
  return this->nodelist.size();
}

// nodelist::getRandomNode
// Descripton - random하게 노드를 반환
// return - node* , NULL
node* nodelist::getRandomNode(){
  std::srand(std::time(NULL));
  size_t list_size = this->nodelist.size();
  int rndInt = rand()/(std::RAND_MAX/list_size+1);
  for(std::list<node*>::iterator pick = this->nodelist.begin();pick!=this->nodelist.end() and rndInt!=0;pick++){
    rndInt--;
  }
  return *pick;
}

// nodelist::appendNode
// Desciption - nodelist에 새 node를 추가함. 단, nodelist에 같은 GithubID나 IP가 존재하면 무시(실패 취급)
// return - True(성공), False(실패)
bool nodelist::appendNode(node* append_node){
  try{
    this->nodelist.push_bach(append_node);
  }
  catch(int exception){
    return false;
  }
  return true;
}
