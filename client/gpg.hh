#ifndef __gpg__
#define __gpg__

namespace gpg{
  char* encBytestream(char* src);
  bool keyRefresh();
  char* decBytestream(char* src);
  bool recvPubKey(string PubKeyID);
}

#endif
