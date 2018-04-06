#ifndef __ui__
#define __ui__
#include "heartbeat.hh"
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <string>


namespace ui{
  void printBanner();
  string getIPAddr();
  userInfo login();
  void clearScreen();
  void* userInput(void* args);
}

#endif
