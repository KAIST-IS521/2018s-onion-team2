
#ifndef __gpg__
#define __gpg__
#define BYTE unsigned char

namespace gpg{
  BYTE* encBytestream();
  bool keyRefresh();
  BYTE* decBytestream();
  bool recvPubKey();
}

#endif
