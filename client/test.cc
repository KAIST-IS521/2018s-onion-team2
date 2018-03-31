#include "util.hh"
#include "ui.hh"
#include "timestamp.hh"
using namespace std;

// To compile this code:
//    g++ test.cc util.cc ui.cc userInfo.cc heartbeat.cc nodelist.cc timestamp.cc -o test

int main()
{
  /*
    This code is to test in_addr_t2byte and byte2in_addr_t function in util.hh
  */
  string IP = ui::getIPAddr();
  cout << IP << endl;
  char ip_byte[IP_SIZE];
  util::ip2byte(IP, ip_byte);
  cout << util::byte2ip(ip_byte) << endl << endl;

  /*
    This code is to test int2byte and byte2int function in util.hh
  */

  char temp[2+INT_SIZE];
  memcpy(temp, "\x00\x01", 2);
  util::int2byte(123456789, temp+2);

  char integer[INT_SIZE];
  memcpy(integer, temp+2, INT_SIZE);
  cout << util::byte2int(integer) << endl << endl;

  /*
    This code is to test time_t2byte and byte2time_t function in util.hh
  */

  time_t timestamp = timestamp::getTimestampNow();
  cout << timestamp << endl;
  char temp2[2+TIME_T_SIZE];
  memcpy(temp2, "\x00\x01", 2);
  util::time_t2byte(timestamp, temp2+2);

  char t[TIME_T_SIZE];
  memcpy(t, temp2+2, TIME_T_SIZE);
  cout << util::byte2time_t(t) << endl;

  return 0;
}
