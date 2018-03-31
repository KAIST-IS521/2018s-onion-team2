#include "util.hh"
#include <cstring>

void util::int2byte(int integer, char* byte){
  union util::int_byte x;
  x.integer = integer;
  strncpy(byte, x.byte, INT_SIZE);
}

int util::byte2int(char* integer){
  union util::int_byte x;
  strncpy(x.byte, integer, INT_SIZE);
  return x.integer;
}

void util::time_t2byte(time_t t, char* byte){
  union util::time_t_byte x;
  x.t = t;
  strncpy(byte, x.byte, TIME_T_SIZE);
}

time_t util::byte2time_t(char* t){
  union util::time_t_byte x;
  strncpy(x.byte, t, TIME_T_SIZE);
  return x.t;
}