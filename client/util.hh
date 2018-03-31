#ifndef __UTIL__
#define __UTIL__
#define TIME_T_SIZE 8
#define INT_SIZE 4
#include <time.h>
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
}

#endif