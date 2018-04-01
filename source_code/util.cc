#include "util.hh"
#include <cstring>
#include <cassert>

pthread_mutex_t m_node_list = PTHREAD_MUTEX_INITIALIZER;
nodelist node_list;

// void packet::insertPkt(char* buf){
//   char* data = new char[MAX_LEN];
//   memcpy(data, buf, MAX_LEN);
//   this->pkt.push_back(data);
// }

// bool packet::getPkt(char* buf){
//   if (this->pkt.empty())
//     return false;
//   char* data = this->pkt.front();
//   memcpy(buf, data, MAX_LEN);
//   delete data;
//   this->pkt.pop_front();
//   return true;
// }

// packet::~packet(){
//   for(list<char*>::iterator it = this->pkt.begin(); it != this->pkt.end(); ++it)
//     delete *it;  
// }

void util::int2byte(int integer, char* byte){
  union util::int_byte x;
  x.integer = integer;
  memcpy(byte, x.byte, INT_SIZE);
}

int util::byte2int(char* integer){
  union util::int_byte x;
  memcpy(x.byte, integer, INT_SIZE);
  return x.integer;
}

// void util::time_t2byte(time_t t, char* byte){
//   union util::time_t_byte x;
//   x.t = t;
//   memcpy(byte, x.byte, TIME_T_SIZE);
// }

// time_t util::byte2time_t(char* t){
//   union util::time_t_byte x;
//   memcpy(x.byte, t, TIME_T_SIZE);
//   return x.t;
// }

void util::ip2byte(string IP, unsigned char* byte){
  int i = 0;
  char *ch = strtok((char*)IP.c_str(), ".");
  while (ch != NULL)
  {
    byte[i++]= atoi(ch);
    ch = strtok(NULL, ".");
  }
  assert(i == IP_SIZE);
}

string util::byte2ip(unsigned char* byte){
  string IP;
  for (int i = 0; i < IP_SIZE; ++i) {
    if(i != IP_SIZE-1)
      IP += to_string(byte[i]) + ".";
    else
      IP += to_string(byte[i]);
  }
  return IP;
}