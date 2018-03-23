
#ifndef __gpg__
#define __gpg__
#define BYTE unsigned char

namespace gpg{
  BYTE* encBytestream(BYTE* src);
  bool keyRefresh();
  BYTE* decBytestream(BYTE* src);
  bool recvPubKey(String PubKeyID);
}

#endif
