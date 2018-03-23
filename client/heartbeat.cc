#include "heartbeat.hh"



// heartbeat::heartbeat
// Description - heartbeat 생성자
// return - None
heartbeat::heartbeat(BYTE* _OneTimeKey, long _timestamp){

}

// heartbeat::getOneTimeKey
// Description - heartbeat 객체에서 OntTimeKey를 가져옴
// return - Null(실패), BYTE*(OneTimeKey stream)
BYTE* heartbeat::getOneTimeKey(){

}

// heartbeat::getTimestamp
// Description - heartbeat 객체에서 Timestamp를 가져옴
// return - Null(실패), long(Timestamp)
long heartbeat::getTimestamp(){

}


// heartbeat::setOntTimeKey
// Description - heartbeat 객체에 OntTimeKey를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setOntTimeKey(BYTE* _OneTimeKey){

}


// heartbeat::recvHeartbeat
// Description - heartbeat 객체에 Timestamp를 세팅함
// return - True(성공), False(실패)
bool heartbeat::setTimestamp(long _timestamp){

}

// hbd::recvHeartbeat
// Description - 서버로부터 heartbeat 메시지를 받았는지를 확인하는 함수
// return - Null(실패), BYTE*
BYTE* hbd::recvHeartbeat()
{

}

// hbd::heartbeatListener
// Description - heartbeat 메세지 송신대기 함수
// return - None
void hbd::heartbeatListener()
{

}

// hbd::SendHeartbeat
// Description - 서버에게 heartbeat 메시지를 전달하는 함수
// return - 전달했으면 true, 아니면 false
bool hbd::sendHeartbeat(BYTE* send_source)
{

}
