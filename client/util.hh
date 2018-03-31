#ifndef __UTIL__
#define __UTIL__
#define TIME_T_SIZE 8
#define INT_SIZE 4
#define IP_SIZE 4
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
using namespace std;

namespace util{
  union int_byte {
    int integer;
    char byte[INT_SIZE];
  };

  union time_t_byte {
    time_t t;
    char byte[TIME_T_SIZE];
  };

  void int2byte(int integer, char* byte);
  int byte2int(char* integer);
  void time_t2byte(time_t t, char* byte);
  time_t byte2time_t(char* t);
  void ip2byte(string IP, unsigned char* byte);
  string byte2ip(unsigned char* byte);
}

#endif