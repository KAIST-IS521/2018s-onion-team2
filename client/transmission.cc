#include "transmission.hh"
#include <iostream>

using namespace tmd;

// tmd::tmdReciver
// Description - tmdReciverMain 에서 thread로 돌릴 함수, port를 계속 listen 하고 있음
// Return - Null(실패) or 받은 패킷의 개인키 복호화된 BYTE Strea
BYTE* tmd::tmdReciver(int port){
}

// tmd::tmdReciverMain
// Description - 지속적으로 tmdReciver 함수를 돌림. tmdReciver에서 반환한 BYTE STREAM을 처리하고 계속 돌아야함.
// Return - 0(정상 종료), -1(이상 종료) // 구현하기 힘들면 void로 변경해도 무방.
int tmd::tmdReciverMain(){
}

// tmd::tmdPathSelecter
// Description - 타 클라이언트로 메세지 전송시 Path를 결정. nodes 만큼의 클라이언트를 거치도록 만들어줌
// Return - IP 배열  or Null(실패)
String* tmd::tmdPathSelecter(int nodes){

}

// tmd::tmdPackPacket
// Desctiption - 평문 BYTE stream을 송신자와 Path 순서 대로 암호화를 한다.
// Return - 암호화된 BYTE stream
BYTE* tmd::tmdPackPacket(BYTE* plain){

}

// tmd::tmdSender
// Description - BYTE stream을 특정 IP로 전송함.
// Return - True(성공), False(실패)
bool tmd::tmdSender(String IP, BYTE* scheme){

}

