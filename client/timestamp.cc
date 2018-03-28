#include "timestamp.hh"

using namespace std;

time_t timestamp::getTimestampNow(){
  return time(NULL);
  
}

string timestamp::timestamp2str(time_t _timestamp){
  stringstream transfer;
  transfer << _timestamp;
  return transfer.str();
}

char* timestamp::timestamp2byte(time_t _timestamp){
  string retstr = timestamp::timestamp2str(_timestamp);
  return const_cast<char*>(retstr.c_str());
}

time_t timestamp::byte2timestamp(char* _timestamp){
  string tmp_timestamp(_timestamp);
  stringstream transfer(tmp_timestamp);
  time_t ret_value;
  transfer >> ret_value;
  return ret_value;
}
  
