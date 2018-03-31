#include "util.hh"
#include "ui.hh"
#include <cstring>

using namespace std;

// To compile this code:
//    g++ test.cc util.cc ui.cc userInfo.cc heartbeat.cc nodelist.cc -o test

int main()
{
  /*
    This code is to test getIPAdder in ui.hh
  */

  cout << ui::getIPAddr() << endl;

  /*
    This code is to test int2byte and byte2int funfction in util.hh
  */

  char temp[6];
  strncpy(temp, "\x00\x01", 2);
  util::int2byte(12345, temp+2);
  strncpy(temp, "\x02\x03", 2);

  char integer[4];
  strncpy(integer, temp+2, 4);
  cout << util::byte2int(integer) << endl;
  return 0;
}
