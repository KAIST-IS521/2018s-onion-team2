#ifndef __ui__
#define __ui__
#include "userInfo.hh"

namespace ui{
  void printBanner();
  string getIPAddr();
  userInfo login();
  void clearScreen();
  void* userInput(void* args);
}

#endif
