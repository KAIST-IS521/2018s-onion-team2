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
  char* tmpMsg = new char[*tmpMsgLen+1];
  bzero(tmpMsg, *tmpMsgLen+1);
  memcpy(tmpMsg,stream+21+*tmpGithubIDLen,*tmpMsgLen);
  string MSG(tmpMsg);
  temp = new message(MSG,ID,tmpOTK,tmpTstamp);
  delete tmpTimestamp;
  delete tmpGithubID;
  delete tmpMsg;
  return temp; 
}

// parser::nodeParser
// Description - 0x02(리스트) char stream에 대한 Parsing을 실시하고 node 객체 형태로 반환
// Return - Null(실패), node*
node* parser::nodeParser(char* stream){
  if (stream[0] != '\x02'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  char tmpPK[9];
  bzero(tmpPK, 9);
  memcpy(tmpPK, stream+6, 8);
  string PK(tmpPK);

  unsigned char tmpAddr[4];
  memcpy(tmpAddr, stream+14, 4);
  string IP(util::byte2ip(tmpAddr));

  int GithubIDLen = util::byte2int(stream+18);
  char* tmpGithubID = new char[GithubIDLen+1];
  bzero(tmpGithubID, GithubIDLen+1);
  memcpy(tmpGithubID, stream+22, GithubIDLen);
  string ID(tmpGithubID);
  delete tmpGithubID;

  return new node(ID, PK, IP);
}

// char parser::getListmode(char*stream){
//   return stream[5];
// }

// // parser::hbParser
// // Description - 0x04(heartbeat) char stream에 대한 Parsing을 실시하고 heartbeat형태로 반환
// // Return - Null(실패), heartbeat*
// heartbeat* parser::hbParser(char* stream){
//   heartbeat* temp;
//   if (stream[0] != '\x04'){
//     cout << "Wrong Parser" << endl;
//     return NULL;
//   }

//   char* OTK = new char[4];
//   memcpy(OTK, stream+1, 4);

//   char* TS = new char[4];     // TS도 9~12바이트가 되야함. (4바이트)
//   memcpy(TS,stream+5,4);
  
//   temp = new heartbeat(OTK,timestamp::byte2timestamp(TS));
//   delete TS;
//   return temp;
// }

// parser::encMessageParser
// Description - 0x00(Encrypted Message) char stream에 대한 Parser을 실시하고 encMessage 객체 형태로 반환
// Return - Null(실패), encMessage*
encMessage* parser::encMessageParser(char* stream){
  encMessage* temp = new encMessage();
  if (stream[0] != '\x00'){
    cout << "Wrong Parser" << endl;
    return NULL;
  }

  unsigned char* tmpIP = new unsigned char[4];
  memcpy(tmpIP,stream+1,4);
  if (!temp->setNextIP(util::byte2ip(tmpIP))){           // char to IP String
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
int parser::packEncMessage(char* stream,encMessage* src){
  int msgSize = src->encMessage::getEncData().size();

  try{
    stream[0] = '\x00';
    unsigned char* tmpIP = new unsigned char[4];
    util::ip2byte(src->encMessage::getNextIP(),tmpIP);
    memcpy(stream+1, tmpIP ,4);                                  // IP to char*
//    memcpy(stream+5, util::int2byte(msgSize).c_str(),4);
    util::int2byte(msgSize,stream+5);
    memcpy(stream+9, (src->encMessage::getEncData()).c_str(),msgSize);
    delete tmpIP;
  }
  catch(int exception){
    delete stream;
    return 0;
  }
  return 9+msgSize;
}

// parser::packMessage
// Description - message의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - return stream의 length
int parser::packMessage(char* stream,message* src,string IP){
  int msgSize = src->message::getContents().size();
  int GithubIDSize = src->message::getGithubID().size();

  unsigned char* tmpIP = new unsigned char[4];
  util::ip2byte(IP.c_str(),tmpIP);
  try{
    stream[0] = '\x01';
    memcpy(stream+1, tmpIP,4);                                   // IP to char*
    memcpy(stream+5, src->message::getOneTimeKey(),4);
    memcpy(stream+9, timestamp::timestamp2byte(src->message::getTimestamp()),4);
//    memcpy(stream+13,util::int2byte(GithubIDSize).c_str(),4);
    util::int2byte(GithubIDSize,stream+13);
    memcpy(stream+17,src->message::getGithubID().c_str(),GithubIDSize);
//    memcpy(stream+17+GithubIDSize, util::int2byte(msgSize), 4);
    util::int2byte(msgSize,stream+17+GithubIDSize);
    memcpy(stream+17+GithubIDSize+4, src->message::getContents().c_str(), msgSize);
  }
  catch(int exception){
    delete tmpIP;
    delete stream;
    return 0;
  }
  delete tmpIP;
  return (21+GithubIDSize+msgSize);
}

// parser::packNode
// Description - node의 요소들을 송신 규격에 맞게 packing 하여 char*으로 반환
// Return - Null(실패), char*(Packing 된 BYTE stream)
int parser::packNode(char* stream, node* src, char mode){
  if(src->getGithubID().empty()){
    return 0;
  }
  int GithubIDSize = src->node::getGithubID().size();
  unsigned char* tmpIP = new unsigned char[4];
  util::ip2byte(src->node::getIP().c_str(),tmpIP);
  try{
    stream[0] = '\x02';
    memcpy(stream+1, timestamp::timestamp2byte(timestamp::getTimestampNow()),4);
    stream[5] = mode;
    memcpy(stream+6,src->node::getPubKeyID().c_str(),8);
    memcpy(stream+14,tmpIP,4);                                 // STR to CHAR* 추가
//    memcpy(stream+18,util::int2byte(GithubIDSize).c_str(),4);
    util::int2byte(GithubIDSize,stream+18);
    memcpy(stream+22,src->node::getGithubID().c_str(),GithubIDSize);
  }catch(int exception){
    delete stream;
    delete tmpIP;
    return 0;
  }
  delete tmpIP;
  return 22+GithubIDSize;
}

// parser::packHeartBeat
// Description - heartbeat의 요소들을 송신 규격에 맞게 packing하여 char*로 반환
// Return - Null(실패), char(Packing 된 BYTE stream)
int parser::packHeartBeat(char* stream, char* OTK){
  if(stream==NULL){
    return 0;
  }
  try{
    stream[0] = '\x04'; 
    memcpy(stream+1, OTK,4);
    char* time_stamp = timestamp::timestamp2byte(timestamp::getTimestampNow());
    memcpy(stream+5, time_stamp, 4);
    delete time_stamp;
  }
  catch(int exception){
    return 0;
  }
  return 9;
}

int parser::getMessagePackLen(message* src){
  return 21+(src->message::getGithubID().size())+(src->message::getContents().size());
}

int parser::getEncMessagePackLen(encMessage* src){
  return 9+(src->encMessage::getEncData().size());
}

// int parser::getNodePackLen(node* src){
//   return 22+(src->node::getGithubID().size());
// }

// int parser::getHeartBeatPackLen(heartbeat* src){
//   return 9;
// }

void parser::packListUpdate(char mode, struct tmd::arg_data* args){
  args->length = 10 + TIME_T_SIZE + IP_SIZE + INT_SIZE + user.getGithubID().length();
  args->data = new char[args->length];
  args->data[0] = '\x02';
  
  char* time_stamp = timestamp::timestamp2byte(timestamp::getTimestampNow());
  memcpy(args->data+1, time_stamp, TIME_T_SIZE);
  delete time_stamp;

  args->data[1+TIME_T_SIZE] = mode;
  memcpy(args->data+2+TIME_T_SIZE, user.getPubKeyID().c_str(), 8);
  util::ip2byte(user.getIP(), (unsigned char*)args->data+10+TIME_T_SIZE);
  util::int2byte(user.getGithubID().length(), args->data+10+TIME_T_SIZE+IP_SIZE);
  memcpy(args->data+10+TIME_T_SIZE+IP_SIZE+INT_SIZE, user.getGithubID().c_str(), user.getGithubID().length());
  args->IP = SERVER_ADDR;
}
