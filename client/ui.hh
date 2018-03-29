#ifndef __ui__
#define __ui__
#include "userInfo.hh"

namespace ui{
  string getIPAddr();
  void printBanner(userInfo user);
  userInfo login();
  void clearScreen();
  void printMessages(string githubID);
}

#endif
