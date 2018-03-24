#include "timestamp.hh"
using namespace std;

time_t timestamp::stgetTimestampNow(){
  return time(NULL);
  
}

string timestamp::timestamp2str(time_t timestamp){
  string retString(ctime(timestamp));
  return retString;
}

char* timestamp::timestamp2byte(time_t timestamp){
  return ctime(timestamp);
}

time_t timestamp::char2timestamp(char* timestamp){
  string tmp_timestamp(timestamp);
  stringstream transfer(tmp_timestamp);
  time_t ret_value;
  tranfer >> ret_value
  return ret_value;
}
  
