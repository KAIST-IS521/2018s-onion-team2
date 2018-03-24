#include "parser.hh"
#include <iostream>

// parser::streamParser
// Description - stream의 Flag를 확인하여 이어서 오는 char stream의 형태를 확인하고 각 형태의 Parser로 넘겨줌
// Return - True(성공), False(실패) 
bool parser::streamParser(char* stream){
}

// parser::messageParser
// Description - 0x00(평문) char stream에 대한 Parsing을 실시하고 message 객체 형태로 반환
// Return - Null(실패), message*
message* parser::message㎩rser(char* stream){
}

// parser::listParser
// Description - 0x02(리스트) char stream에 대한 Parsing을 실시하고 node 객체 형태로 반환
// Return - Null(실패), node*
node* parser::list㎩rser(char* stream){
}

// parser::hbParser
// Description - 0x04(heartbeat) char stream에 대한 Parsing을 실시하고 heartbeat형태로 반환
// Return - Null(실패), heartbeat* 
heartbeat* parser::hbParser(char* stream){
}

// parser::encMessageParser
// Description - 0x01(Encrypted Message) char stream에 대한 Parser을 실시하고 encMessage 객체 형태로 반환
// Return - Null(실패), encMessage*
encMessage* parser::encMessageParser(char* stream){
}

// parser::packEncMessage
// Description - encMessage의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packEncMessage(encMessage* src){
}

// parser::packMessage
// Description - message의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packMessage(message* src){

}

// parser::packNode
// Description - node의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packNode(node* src){

}

// parser::packHeartBeat
// Description - heartbeat의 요소들을 송신 규격에 맞게 packing하여 char*로 반환
// Return - Null(실패), char(Packing 된 BYTE strea)
char* parser::packHeartBeat(heartbeat* src){

}

