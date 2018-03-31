#include "util.hh"
#include <cstring>

void util::int2byte(int integer, char* byte){
  union util::uni x;
  x.integer = integer;
  strncpy(byte, x.byte, 4);
}

int util::byte2int(char* integer){
  union util::uni x;
  strncpy(x.byte, integer, 4);
  return x.integer;
}