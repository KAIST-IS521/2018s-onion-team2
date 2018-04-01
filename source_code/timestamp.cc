#include "timestamp.hh"

using namespace std;

time_t timestamp::getTimestampNow(){
  return time(NULL);
  
}

string timestamp::timestamp2str(time_t _timestamp){
  std::tm tm = *std::localtime(&_timestamp);
  std::stringstream ss;
  ss << std::put_time(&tm, "%F %T");
  return ss.str();
}

char* timestamp::timestamp2byte(time_t _timestamp){
    size_t i;
    char *str = new char[5];
    bzero(str,5);
    unsigned char *ptr = (unsigned char *)&_timestamp;
    for(i = 0; i < sizeof(time_t)-4; i++) {
       sprintf(&str[i], "%c", ptr[i]);
    }
    return str;
}

time_t timestamp::byte2timestamp(char* _timestamp){
  time_t ret = 0;
  strncpy((char*)&ret,_timestamp,4);
  return (time_t)ret;
}