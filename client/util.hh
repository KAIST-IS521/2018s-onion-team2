#ifndef __UTIL__
#define __UTIL__
#include <string>
using namespace std;

namespace util{
  union uni {
    int integer;
    char byte[4];
  };
  void int2byte(int integer, char* byte);
  int byte2int(char* integer);
}

#endif