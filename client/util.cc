#include "util.hh"
#include <cstring>

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

void util::time_t2byte(time_t t, char* byte){
  union util::time_t_byte x;
  x.t = t;
  memcpy(byte, x.byte, TIME_T_SIZE);
}

time_t util::byte2time_t(char* t){
  union util::time_t_byte x;
  memcpy(x.byte, t, TIME_T_SIZE);
  return x.t;
}

void util::ip2byte(string IP, char* byte){
  union util::in_addr_t_byte x;
  struct sockaddr_in adr_inet;

  inet_aton(IP.c_str(), &adr_inet.sin_addr);
  x.IP[0] = inet_netof(adr_inet.sin_addr);
  x.IP[1] = inet_lnaof(adr_inet.sin_addr);
  memcpy(byte, x.byte, IP_SIZE);
}

string util::byte2ip(char* byte){
  union util::in_addr_t_byte x;
  memcpy(x.byte, byte, IP_SIZE);
  return inet_ntoa(inet_makeaddr(x.IP[0], x.IP[1]));
}