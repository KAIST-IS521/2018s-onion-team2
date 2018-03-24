#include "gpg.hh"

using namespace gpg;

// gpg::encBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg encryption을 수행하고 결과를 반환
// Return - Encrypted Byte* or Null(실패 시)
char* gpg::encBytestream(char* src){

}

// gpg::keyRefresh
// Description - fork-exec를 통해 gpg --refresh 를 수행
// Return - True(성공), False(실패)
bool gpg::keyRefresh(){

}

// gpg::decBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg decription을 수행하고 결과를 반환
// Return - Plain char* or Null(실패 시)
char* gpg::decBytestream(char* src){

}

// gpg::recvPubKey
// Description - PubKeyID에 해당하는 PublicKey를 keyserver로부터 받는 gpg --recv-key를 수행(fork-exec) 사용
// Return - True(성공), False(실패)
bool gpg::recvPubKey(string PubKeyID){
 

}

