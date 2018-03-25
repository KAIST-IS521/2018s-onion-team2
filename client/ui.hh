#ifndef __ui__
#define __ui__
#include <iostream>
#include "userInfo.hh"

namespace ui{
  void printBanner(userInfo user);
  userInfo login();
  void clearScreen();
  void printMessage(string githubID);
}

#endif
