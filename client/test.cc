#include "util.hh"
#include "ui.hh"
#include "timestamp.hh"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

// To compile this code:
//    g++ test.cc util.cc ui.cc userInfo.cc heartbeat.cc nodelist.cc -o test

int main()
{
  /*
    This code is to test getIPAdder in ui.hh and show how to convert IPv4 address to ip_addr_t.
  */

  cout << ui::getIPAddr() << endl;
  cout << inet_addr(ui::getIPAddr().c_str()) << endl << endl;

  /*
    This code is to test int2byte and byte2int function in util.hh
  */

  char temp[2+INT_SIZE];
  strncpy(temp, "\x00\x01", 2);
  util::int2byte(123456789, temp+2);

  char integer[INT_SIZE];
  strncpy(integer, temp+2, INT_SIZE);
  cout << util::byte2int(integer) << endl << endl;

  /*
    This code is to test time_t2byte and byte2time_t function in util.hh
  */

  time_t timestamp = timestamp::getTimestampNow();
  cout << timestamp << endl;
  char temp2[2+TIME_T_SIZE];
  strncpy(temp2, "\x00\x01", 2);
  util::time_t2byte(timestamp, temp2+2);

  char t[TIME_T_SIZE];
  strncpy(t, temp2+2, TIME_T_SIZE);
  cout << util::byte2time_t(t) << endl;

  return 0;
}
