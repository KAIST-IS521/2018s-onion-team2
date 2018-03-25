#include "parser.hh"
#include <iostream>
#include <cstring>
using namespace std;


// parser::messageParser
// Description - 0x00(평문) char stream에 대한 Parsing을 실시하고 message 객체 형태로 반환
// Return - Null(실패), message*
message* parser::message㎩rser(char* stream){
  message* temp;
  if (steam[0] != 0){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* OTK = stream[5];    // OTK가 5~8바이트가 되야함. (4바이트)
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
  string ID = NULL;
  memcpy(ID, stream[17], ID_length);
  if (!temp->setGithubID(ID) || length > 39){
    cout << "Wrong GithubID" << endl;
    return NULL;
  }

  unsigned int msg_length = stream[17+ID_length];     // message의 length가 되야햠. (4바이트)
  string msg = NULL;
  memcpy(msg, stream[21+ID_length], msg_length);

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
    memcpy(PK, stream[6], 8);

    string IP = NULL;
    memcpy(PK, stream[14], 4);

    unsigned int ID_length = stream[18];
    if (ID_length > 39){
      cout << "Wrong GithubID length" << endl;
      return NULL;
    }
    string ID = NULL;
    memcpy(ID, stream[22], ID_length);

    *temp = node(ID, PK, IP);
  }

  else if (stream[5] == 1){
    string msg = NULL;
    memcpy(msg, stream[6], 8);
  }

  return temp;
}

// parser::hbParser
// Description - 0x04(heartbeat) char stream에 대한 Parsing을 실시하고 heartbeat형태로 반환
// Return - Null(실패), heartbeat*
heartbeat* parser::hbParser(char* stream){
  heartbeat* temp;
  if (steam[0] != 4){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* OTK = stream[5];    // OTK가 5~8바이트가 되야함. (4바이트)
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

  string next_IP = NULL;
  memcpy(next_IP, stream[1], 4);
  if (!temp->setNextIP(next_IP)){
    cout << "Wrong Next IP" << endl;
    return NULL;
  }

  unsigned int enc_data_length = stream[5];
  char* enc_data = stream[9];                     // 이부분은 고쳐야함.
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
  int length = strlen(src->getEncData());
  char* stream = new char[9+length];

  stream[0] = 0;
  stream[1] = src->getNextIP();
  stream[5] = strlen(src->getEncData());
  stream[9] = src->getEncData();

  return stream;
}

// parser::packMessage
// Description - message의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packMessage(message* src){
  char* stream = NULL;
  stream[0] = 1;
  stream[1] = src->getNextIP();
  stream[5] = src->getOneTimeKey();
  stream[9] = src->getTimestamp();
  stream[13] = strlen(src->getGithubID());
  stream[17] = src->getGithubID();
  stream[17+strlen(src->getGithubID()] = strlen(src->getContents());
  stream[21+strlen(src->getGithubID()] = src->getContents();

  return stream;
}

// parser::packNode
// Description - node의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packNode(node* src){
  char* stream = NULL;
  stream[0] = 2;
  stream[1] = src->getTimestamp();            // node에는 timestamp 관련 변수나 함수가 없음.
  stream[5] =                                 // mode관련 변수가 없음.
  stream[6] = src->getPubKeyID();
  stream[14] = src->getIP();
  stream[18] = strlen(src->getGithubID());
  stream[22] = src->getGithubID();

  return stream;

}

// parser::packHeartBeat
// Description - heartbeat의 요소들을 송신 규격에 맞게 packing하여 char*로 반환
// Return - Null(실패), char(Packing 된 BYTE strea)
char* parser::packHeartBeat(heartbeat* src){
  char* stream = NULL;
  stream[0] = 4;
  stream[1] = src->getOneTimeKey();
  stream[5] = src->getTimestamp();

  return stream;
}
