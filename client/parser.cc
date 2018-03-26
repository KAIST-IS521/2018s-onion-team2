#include "parser.hh"
#include <iostream>
#include <cstring>
using namespace std;


// parser::messageParser
// Description - 0x00(평문) char stream에 대한 Parsing을 실시하고 message 객체 형태로 반환
// Return - Null(실패), message*
message* parser::message㎩rser(char* stream){
  message* temp = new message;
  if (steam[0] != 0){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char OTK[4];
  strncpy(OTK, &stream[5], 4);          // OTK가 5~8바이트가 되야함. (4바이트)
  if (!temp->setOneTimeKey(OTK)){
    cout << "Wrong OneTimeKey" << endl;
    return NULL;
  }

  time_t TS = stream[9];     // TS도 9~12바이트가 되야함. (4바이트)
  if (!temp->setTimestamp(TS)){
    cout << "Wrong Timestamp" << endl;
    return NULL;
  }

  unsigned int ID_length = stream[13];     // GithubID의 length가 되야함. (4바이트)
  String ID = "";
  for (int i = 0; i<msg_length; i++){
    ID += stream[17+i];
  }
  if (!temp->setGithubID(ID) || ID_length > 39){
    cout << "Wrong GithubID" << endl;
    return NULL;
  }

  unsigned int msg_length = stream[17+ID_length];     // message의 length가 되야햠. (4바이트)
  string msg = "";
  for (int i = 0; i<msg_length; i++){
    msg += stream[21+i];
  }

  if (!temp->setMessage(msg)){
    cout << "Wrong Message" << endl;
    return NULL;
  }
  return temp;
}

// parser::listParser
// Description - 0x02(리스트) char stream에 대한 Parsing을 실시하고 node 객체 형태로 반환
// Return - Null(실패), node*
node* parser::list㎩rser(char* stream){
  node* temp;
  if (steam[0] != 2){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  if (stream[5] == 0){
    string PK = NULL;
    memcpy(PK, &stream[6], 8);

    string IP = NULL;
    memcpy(PK, &stream[14], 4);

    unsigned int ID_length = stream[18];
    if (ID_length > 39){
      cout << "Wrong GithubID length" << endl;
      return NULL;
    }
    string ID = "";
    for (int i = 0; i<ID_length; i++){
      ID += stream[22+i];
    }

    *temp = node(ID, PK, IP);
  }

  else if (stream[5] == 1){                   // MODE가 삭제인 경우. 아직 코딩 못함.
    string msg = "";
    for (int i = 0; i<8; i++){
      msg += stream[6+i];
    }
  }

  return temp;
}

// parser::hbParser
// Description - 0x04(heartbeat) char stream에 대한 Parsing을 실시하고 heartbeat형태로 반환
// Return - Null(실패), heartbeat*
heartbeat* parser::hbParser(char* stream){
  heartbeat* temp;
  if (stream[0] != 4){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char OTK[4];
  strncpy(OTK, &stream[1], 4);

  if (!temp->setOneTimeKey(OTK)){
    cout << "Wrong OneTimeKey" << endl;
    return NULL;
  }

  time_t TS = stream[9];     // TS도 9~12바이트가 되야함. (4바이트)
  if (!temp->setTimestamp(TS)){
    cout << "Wrong Timestamp" << endl;
    return NULL;
  }

  return temp;
}

// parser::encMessageParser
// Description - 0x01(Encrypted Message) char stream에 대한 Parser을 실시하고 encMessage 객체 형태로 반환
// Return - Null(실패), encMessage*
encMessage* parser::encMessageParser(char* stream,string IP){
  encMessage* temp;
  if (steam[0] != 0){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  string next_IP = "";
  for (int i = 0; i<4; i++){
    next_IP += stream[1+i];
  }
  if (!temp->setNextIP(next_IP)){
    cout << "Wrong Next IP" << endl;
    return NULL;
  }

  unsigned int enc_data_length = stream[5];
  char* enc_data;
  strncpy(enc_data, &stream[9], enc_data_length);
  if (!temp->setEncData(enc_data)){
    cout << "Wrong Encrypted Data" << endl;
    return NULL;
  }

  return temp;
}

// parser::packEncMessage
// Description - encMessage의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packEncMessage(encMessage* src){
  char* stream = "0";

  char IP[4] = src->getNextIP();
  strcat(stream, IP);
  int data_length = strlen(src->getEncData());
  strncat(stream, (char)data_length, 4);
  strcat(stream, src->getEncData());

  return stream;
}

// parser::packMessage
// Description - message의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packMessage(message* src){
  char* stream = "1";
  strcat(stream, src->getNextIP());
  strcat(stream, src->getOneTimeKey());
  strcat(stream, src->getTimestamp());

  int ID_length = strlen(src->getGithubID());
  strncat(stream, (char)ID_length, 4);

  strcat(stream, src->getGithubID());

  int con_length = strlen(src->getContents());
  strncat(stream, (char)con_length, 4);

  strcat(stream, src->getContents());

  return stream;
}

// parser::packNode
// Description - node의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packNode(node* src){
  char* stream = "2";
  strcat(stream, src->getTimestamp());        // node에는 timestamp 관련 변수나 함수가 없음.
  //strcat(stream, src->);                    // mode관련 변수가 없음.
  strcat(stream, src->getPubKeyID());
  strcat(stream, src->getIP());

  int ID_length = strlen(src->getGithubID());
  strncat(stream, (char)ID_length, 4);

  strcat(stream, src->getGithubID());

  return stream;

}

// parser::packHeartBeat
// Description - heartbeat의 요소들을 송신 규격에 맞게 packing하여 char*로 반환
// Return - Null(실패), char(Packing 된 BYTE strea)
char* parser::packHeartBeat(heartbeat* src){
  char* stream = "4";
  strcat(stream, src->getOneTimeKey());
  strcat(stream, src->getTimestamp());

  return stream;
}
