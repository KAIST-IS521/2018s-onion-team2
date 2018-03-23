
#ifndef __HEARTBEAT__
#define __HEARTBEAT__

class heartbeat{
private:
  long OneTimeKey;
  long timestamp;
public:
  bool recvHeartbeat();
  String ParseMessage();
  bool SendHeartbeat();

}
