#ifndef __gpg__
#define __gpg__

namespace gpg{
  char* encBytestream(char* src, string PubKeyID);
  bool keyRefresh();
  char* decBytestream(char* src, string passphase);
  bool recvPubKey(string PubKeyID);
}

#endif
