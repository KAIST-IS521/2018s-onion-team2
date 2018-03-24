#ifndef __transmission__
#define __transmission__

// tmd = TransMission Daemon
namespace tmd{
  char* tmdReciver(int port);
  int tmdReciverMain();
  string* tmdPathSelecter();
  char* tmdPackPacket(BYTE* plain);
  bool tmdSender(string IP,char* scheme);
}

#endif

