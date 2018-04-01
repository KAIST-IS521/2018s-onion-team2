#include "nodelist.hh"

using namespace std;

node::node(){};

// node::node
// Description - node 객체의 생성자 ( node의 각 요소를 직접 삽입하는 형태 )
// return - None
node::node(string _GithubID, string PubKeyID, string IP){
  this->GithubID = _GithubID;
  this->PubKeyID = PubKeyID;
  this->IP = IP;

  //delete &(_GithubID);
  //delete &(PubKeyID);
  //delete &IP;
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
nodelist::nodelist(){
  this->_nodelist = new list<node*>();
}

// nodelist::searchNode
// Description - Nodelist의 node들 중 주어진 GithubID/IP를 가진 노드의 포인터를 반환
// return - node* or Null
node* nodelist::searchNode(string value, int mode){
  for(std::list<node*>::iterator pick = this->_nodelist->begin();pick!=this->_nodelist->end();pick++){
    if(mode==0){
      if(((*pick)->getGithubID()).compare(value)==0){
        return *pick;
      }
    }
    else if(mode==1){
      if(((*pick)->getIP()).compare(value)==0){
       return *pick;
      }
    }
    else{
      return NULL;
    }
  }
  return NULL;
}

// nodelist::deleteNode
// Desciption - Nodelist의 node 중 주어진 GithubID/IP를 가진 노드의 포인터를 반환
// return - True(성공), False(실패)
bool nodelist::deleteNode(string value, int mode){
  for(list<node*>::iterator pick = this->_nodelist->begin();pick!=this->_nodelist->end();pick++) {
    if(mode == 0){
      if(((*pick)->getGithubID()).compare(value) == 0){
        node* tmp = *pick;
        this->_nodelist->erase(pick);
        delete tmp;
        return true;
      }
    } else if(mode == 1) {
      if(((*pick)->getIP()).compare(value)==0) {
        node* tmp = *pick;
        this->_nodelist->erase(pick);
        delete tmp;
        return true;
      }
    } else {
      return false;
    }
  }
  return false;
}


// nodelist::getNodelistLen
// Desciption - Nodelist의 길이(=Node 수)를 반환
// return - length of Nodelist
int nodelist::getNodelistLen(){
  return this->_nodelist->size();
}

// nodelist::getRandomNode
// Descripton - random하게 노드를 반환
// return - node* , NULL
node* nodelist::getRandomNode(){
  long int rand_seed;
  std::ifstream urand("/dev/urandom");
  urand.read((char*)&rand_seed,sizeof(long int));
  urand.close();
  std::srand(rand_seed);
  size_t list_size = this->_nodelist->size();
  int rndInt = rand()/(RAND_MAX/list_size+1);
  cout << rndInt << endl;
  std::list<node*>::iterator pick;
  for(pick = this->_nodelist->begin();pick!=this->_nodelist->end() and rndInt!=0;pick++){
    rndInt--;
  }
  return *pick;
}

// nodelist::appendNode
// Desciption - nodelist에 새 node를 추가함. 단, nodelist에 같은 GithubID나 IP가 존재하면 무시(실패 취급)
// return - True(성공), False(실패)
bool nodelist::appendNode(node* append_node){
  try{
    this->_nodelist->push_back(append_node);
  }
  catch(int exception){
    return false;
  }
  return true;
}

// nodelist::getGithubIDList()
// Description - 현재 리스트의 GithubID들을 출력함
// return - vector<string>, NULL(실패)
vector<string>* nodelist::getGithubIDList(){
  vector<string>* retIDList = new vector<string>();
  try{
    for(std::list<node*>::iterator pick=this->_nodelist->begin();pick!=this->_nodelist->end();pick++){
      retIDList->push_back((*pick)->getGithubID());
    }
  }
  catch(int exception){
    return NULL;
  }
  return retIDList;
}