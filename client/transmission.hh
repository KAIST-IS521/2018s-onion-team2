#ifndef __transmission__
#define __transmission__

// tmd = TransMission Daemon
namespace tmd{
  char* tmdReciver();
  int tmdReciverMain();
  list<node*> tmdPathSelecter();
  char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
  bool tmdSender(string IP,char* scheme);
}

#endif

