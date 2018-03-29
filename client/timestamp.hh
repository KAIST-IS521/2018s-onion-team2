#ifndef __timestamp__
#define __timestamp__
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace timestamp{
  
  time_t getTimestampNow();
  string timestamp2str(time_t timestamp);
  char* timestamp2byte(time_t timestamp);
  time_t byte2timestamp(char* timestamp);
  

}

#endif
