#ifndef __transmission__
#define __transmission__

// tmd = TransMission Daemon
namespace tmd{
  BYTE* tmdReciver(int port);
  int tmdReciverMain();
  String* tmdPathSelecter();
  BYTE* tmdPackPacket(BYTE* plain);
  bool tmdSender(String IP,BYTE* scheme);
}

#endif

