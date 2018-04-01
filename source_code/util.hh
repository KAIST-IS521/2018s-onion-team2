#ifndef __UTIL__
#define __UTIL__
#define TIME_T_SIZE 4
#define INT_SIZE 4
#define IP_SIZE 4
#define HB_PORT 60750
#define MESSAGE_PORT 56827
#define MAX_LEN 512
#define MAX_QUEUE 5
#define HB_LEN 9
#define SIGN_IN '0x00'
#define SIGN_OUT '0x01'
#define SERVER_ADDR "143.248.249.111"

#include "nodelist.hh"
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <pthread.h>
// #include <list>
using namespace std;

extern nodelist node_list;
extern pthread_mutex_t m_node_list;
// class packet {
// private:
//   list<char*> pkt;
// public:
//   void insertPkt(char* buf);
//   bool getPkt(char* buf);
//   ~packet();
// };

namespace util{
  union int_byte {
    int integer;
    char byte[INT_SIZE];
  };

  // union time_t_byte {
  //   time_t t;
  //   char byte[TIME_T_SIZE];
  // };

  void int2byte(int integer, char* byte);
  int byte2int(char* integer);
  // void time_t2byte(time_t t, char* byte);
  // time_t byte2time_t(char* t);
  void ip2byte(string IP, unsigned char* byte);
  string byte2ip(unsigned char* byte);
}

#endif