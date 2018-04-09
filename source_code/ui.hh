#ifndef __ui__
#define __ui__
#include "userInfo.hh"
#include <stdlib.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <string>


namespace ui{
  void printBanner();
  userInfo login(nodelist* node_list);
  void clearScreen();
  string inputCheck();
  void* userInput(void* args);
}

#endif
