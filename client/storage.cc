#include "storage.hh"
#include <iostream>
#include <sqlite3.h>

// storage::storage
// Description - storage 객체 생성자
// return - None
storage::storage(String path){

}

// storage::storeMessage
// Description - Message 1건을 저장함. 보낸거, 받은거 전부 저장할거임
// return - True(성공), False(실패)
bool storage::storeMessage(message* target){
}

// storage::storeMessage
// Desciption - Message 여러건을 list형태로 받아 저장.
// return - 0(성공), < 0 ( 실패 건수 * -1 )
int storage::storeMessage(list<message> messageList){
}

// storage::loadMessage
// Description - 특정 GithubID와 주고 받은 Message를 조회
// return - Null(실패), list<message> 객체 (성공)
list<message> storage::loadMessage(String GithubID){

}

// storage::loadMessage
// Description - 특정 GithubID와 주고 받은 Message를 조회하되, 최근 n개를 조회한다.
// return - Null(실패), list<message> 객체 (성공)
list<message> storage::loadMessage(String GithubID, int count){

}


