#ifndef __transmission__
#define __transmission__
#define MESSAGE_PORT 56827

// tmd = TransMission Daemon
namespace tmd{
  char* tmdReciver();
  int tmdReciverMain();
  list<node*> tmdPathSelecter();
  char* tmdPackPacket(node* sender, node* reciver, BYTE* plain);
  bool tmdSender(string IP,char* scheme);
}

#endif

