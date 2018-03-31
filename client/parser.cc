#include "parser.hh"
using namespace std;


// parser::messageParser
// Description - 0x01(평문) char stream에 대한 Parsing을 실시하고 message 객체 형태로 반환
// Return - Null(실패), message*
message* parser::messageParser(char* stream){
  message* temp;
  if (stream[0] != '\x01'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* tmpOTK = new char[4];
  memcpy(tmpOTK, stream+5, 4);

  char* tmpTimestamp = new char[4];
  memcpy(tmpTimestamp, stream+9, 4);
  time_t tmpTstamp = timestamp::byte2timestamp(tmpTimestamp);

  int* tmpGithubIDLen = (int*)(stream+13);
  char* tmpGithubID = new char[*tmpGithubIDLen];
  memcpy(tmpGithubID,stream+17,*tmpGithubIDLen);
  string ID(tmpGithubID);

  int* tmpMsgLen = (int*)(stream+17+*tmpGithubIDLen);
  char* tmpMsg = new char[*tmpMsgLen];
  memcpy(tmpMsg,stream+21+*tmpGithubIDLen,*tmpMsgLen);
  string MSG(tmpMsg);
  temp = new message(MSG,ID,tmpOTK,tmpTstamp);
  delete tmpTimestamp;
  delete tmpGithubID;
  delete tmpMsg;
  return temp; 
}

// parser::listParser
// Description - 0x02(리스트) char stream에 대한 Parsing을 실시하고 node 객체 형태로 반환
// Return - Null(실패), node*
node* parser::listParser(char* stream){
  node* temp;
  if (stream[0] != '\x02'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* tmpPK = new char[8];
  memcpy(tmpPK,stream+7,8);
  string PK(tmpPK);

  char* tmpAddr = new char[4];
  memcpy(tmpAddr, stream+15, 4);
  string IP(??); // byte to IP

  int* GithubIDLen = (int*)(stream+18);
  char* tmpGithubID = new char[*GithubIDLen];
  memcpy(tmpGithubID,stream+22,*GithubIDLen);
  string ID(tmpGithubID);
  temp = new node(ID, PK, IP);

  delete tmpPK;
  delete tmpAddr;
  delete tmpGithubID;
  return temp;
}

char parser::getListmode(char*stream){
  return stream[5];
}

// parser::hbParser
// Description - 0x04(heartbeat) char stream에 대한 Parsing을 실시하고 heartbeat형태로 반환
// Return - Null(실패), heartbeat*
heartbeat* parser::hbParser(char* stream){
  heartbeat* temp;
  if (stream[0] != '\x04'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* OTK = new char[4];
  memcpy(OTK, stream+1, 4);

  char* TS = new char[4];     // TS도 9~12바이트가 되야함. (4바이트)
  memcpy(TS,stream+5,4);
  
  temp = new heartbeat(OTK,timestamp::byte2timestamp(TS));
  delete TS;
  return temp;
}

// parser::encMessageParser
// Description - 0x00(Encrypted Message) char stream에 대한 Parser을 실시하고 encMessage 객체 형태로 반환
// Return - Null(실패), encMessage*
encMessage* parser::encMessageParser(char* stream){
  encMessage* temp = new encMessage();
  if (stream[0] != '\x00'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char* tmpIP = new char[4];
  memcpy(tmpIP,stream+1,4);
  if (!temp->setNextIP(tmpIP)){           // char to IP String
    cout << "Wrong Next IP" << endl;
    return NULL;
  }
  delete tmpIP;

  unsigned int* enc_data_length = (unsigned int*)(stream+5);
  char* enc_data_char = new char[*enc_data_length];
  memcpy(enc_data_char, stream+9, *enc_data_length);
  string tmp_str(enc_data_char);
  if (!temp->setEncData(tmp_str)){
    cout << "Wrong Encrypted Data" << endl;
    return NULL;
  }
  delete enc_data_char;
  return temp;
}

// parser::packEncMessage
// Description - encMessage의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packEncMessage(encMessage* src){
  int msgSize = src->encMessage::getEncData().size();

  char* stream = new char[9+msgSize];
  try{
    stream[0] = '\x01';
    memcpy(stream+1, src->encMessage::getNextIP(),4);                                  // IP to char*
    memcpy(stream+5, util::int2byte(msgSize).c_str(),4);
    memcpy(stream+9, (src->encMessage::getEncData()).c_str(),msgSize);
  }
  catch(int exception){
    delete stream;
    return NULL;
  }
  return stream;
}

// parser::packMessage
// Description - message의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packMessage(message* src,string IP){
  int msgSize = src->message::getContents().size();
  int GithubIDSize = src->message::getGithubID().size();

  char* stream = new char[17+msgSize+4+GithubIDSize];
  try{
    stream[0] = '\x00';
    memcpy(stream+1, IP.c_str(),4);                                   // IP to char*
    memcpy(stream+5, src->message::getOneTimeKey(),4);
    memcpy(stream+9, timestamp::timestamp2byte(timestamp::getTimestampNow()),4);
    memcpy(stream+13,util::int2byte(GithubIDSize).c_str(),4);
    memcpy(stream+17,src->message::getGithubID().c_str(),GithubIDSize);
    memcpy(stream+17+GithubIDSize, util::int2byte(msgSize), 4);
    memcpy(stream+17+GithubIDSize+4, src->message::getContents().c_str(), msgSize);
  }
  catch(int exception){
    delete stream;
    return NULL;
  }
  return stream;
}

// parser::packNode
// Description - node의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
char* parser::packNode(node* src, char* mode){
  if(src->getGithubID().empty()){
    return NULL;
  }
  int GithubIDSize = src->node::getGithubID().size();
  char* stream = new char[22+GithubIDSize];
  try{
    stream[0] = '\x01';
    memcpy(stream+1, timestamp::timestamp2byte(timestamp::getTimestampNow()),4);
    stream[5] = mode[0];
    memcpy(stream+6,src->node::getPubKeyID().c_str(),8);
    memcpy(stream+14,src->node::getIP().c_str(),4);                                 // STR to CHAR* 추가
    memcpy(stream+18,util::int2byte(GithubIDSize).c_str(),4);
    memcpy(stream+22,src->node::getGithubID().c_str(),GithubIDSize);
  }catch(int exception){
    delete stream;
    return NULL;
  }
  return stream;
}

// parser::packHeartBeat
// Description - heartbeat의 요소들을 송신 규격에 맞게 packing하여 char*로 반환
// Return - Null(실패), char(Packing 된 BYTE stream)
char* parser::packHeartBeat(heartbeat* src){
  char* stream = new char[9];
  try{
    stream[0] = '\x04'; 
    memcpy(stream+1, src->heartbeat::getOneTimeKey(),4);
    memcpy(stream+5, timestamp::timestamp2byte(src->heartbeat::getTimestamp()),4);
  }
  catch(int exception){
    delete stream;
    return NULL;
  }
  return stream;
}
