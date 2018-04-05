#include "gpg.hh"

using namespace gpg;

/* Referenced - http://fm4dd.com/programming/base64/base64_stringencode_c.htm */
/* Modified by hexife */
char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/* encodeblock - encode 3 8-bit binary bytes as 4 '6-bit' characters */
void encodeblock(unsigned char in[], char b64str[], int len ) {
    unsigned char out[5];
    out[0] = b64[ in[0] >> 2 ];
    out[1] = b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? b64[ ((in[1] & 0x0f) << 2) |
             ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    strncat(b64str, (const char*)out, sizeof(out));
}

/* encode - base64 encode a stream, adding padding if needed */
void b64_encode(char *clrstr, char *b64dst,int length) {
  unsigned char in[3];
  int i, len = 0;
  int j = 0;

  b64dst[0] = '\0';
  while(j<length){
    len = 0;
    for(i=0; i<3; i++) {
     in[i] = (unsigned char) clrstr[j];
     if(j<length) {
        len++; j++;
      }
      else in[i] = 0;
    }
    if( len ) {
      encodeblock( in, b64dst, len );
    }
  }
}


// gpg::encBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg encryption을 수행하고 결과를 반환
// Return - Encrypted Byte* or Null(실패 시)
char* gpg::encBytestream(char* src,string* PubKeyID,int length){
  string prefix_cmd("echo '");
  string middle_cmd("' | base64 -d | gpg --no-tty --batch --logger-fd 1 --always-trust -ear ");
  string suffix_cmd(" 2>/dev/null");

  // checking PUBKEYID
  if(PubKeyID->size()!=8){
    cout << "Length Fault" << endl;
    return NULL;
  }
  else if(not(std::regex_match(*PubKeyID, std::regex("[0-9|A-F]*")))){
    cout << "REGEX Fault" << endl;
    return NULL;
  }
  int count = 0;
  char* plain;
  // checking src (prevent cmd injection)
  for(int i=0;i<length;i++){
    if(src[i]=='\x22' and (i>0 and src[i-1]!='\x5c')){
      count++;
    }
  }
  plain = new char[length+count];
  count = 0;
  for(int i=0;i<length;i++){
    if(src[i]=='\x22' and (i>0 and src[i-1]!='\x5c')){
  plain[i+count] = '\x5c';
  plain[i+count+1] = '\x22';
        count += 1;
    }
    else{
  plain[i] = src[i];
    }
  }

  size_t b64size = ((length+count)%3==0)? ((length+count)/3)*4 : (((length+count)/3)+1)*4;
  char* dst = new char[b64size];
  b64_encode(plain,dst, length+count);
  string full_cmd(prefix_cmd+dst+middle_cmd+*PubKeyID+suffix_cmd);

  char* buf = new char[1024];
  FILE* pp = popen(full_cmd.c_str(),"r");
  string* result = NULL;
  if(pp==NULL){
    cout << "Fail to exec gpg" << endl;
    return NULL;
  }
  while(fgets(buf,1024,pp)){
    if(result==NULL){
      result = new string(buf);
    }
    else{
      result->append(buf);
    }
  }
  delete buf;
  pclose(pp);
  return (char*)(result->c_str());
}

// gpg::keyRefresh
// Description - fork-exec를 통해 gpg --refresh 를 수행
// Return - True(성공), False(실패)
bool gpg::keyRefresh(){
  char* buf = new char[1024];
  FILE* pp = popen("gpg --no-tty --batch --logger-fd 1 --refresh  2>/dev/null","r");
  string* result = NULL;
  if(pp==NULL){
    cout << "Fail to exec gpg" << endl;
    return false;
  }
  while(fgets(buf,1024,pp)){
    if(result==NULL){
      result = new string(buf);
    }
    else{
      result->append(buf);
    }
  }

  if(not(result->find("gpg: Total number processed: ")!=std::string::npos)){
  return false;
  }
  delete buf;
  delete result;
  delete pp;
  pclose(pp);
  return true;
}

// gpg::decBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg decription을 수행하고 결과를 반환
// Return - Plain char* or Null(실패 시)
char* gpg::decBytestream(char* src, string* passphrase){
  string encData(src);
  string prefix_cmd("echo \'");
  string middle_cmd("\' | gpg --no-tty --batch --logger-fd 1 -d --passphrase \'");
  string suffix_cmd("\' 2>/dev/null");

   if(std::regex_search(*passphrase, std::regex("[;|\$\(|\)|\`]"))){
    cout << "REGEX Fault" << endl;
    return NULL;
  }

  string full_cmd(prefix_cmd+encData+middle_cmd+*passphrase+suffix_cmd);
  char* buf = new char[1024];
  FILE* pp = popen(full_cmd.c_str(),"r");
  string* result = NULL;
  if(pp==NULL){
    cout << "Fail to exec gpg" << endl;
    return NULL;
  }
  int now_size = 0;
  while((now_size=fread(buf,1,1024,pp))>0){
    if(result==NULL){
      result = new string(buf,now_size);
    }
    else{
      result->append(buf,now_size);
    }
  }
  for(int i=0;i<3;i++){
  string ret = result->substr(result->find('\x0a')+1);
  delete result;
  result = new string(ret);
  }
  delete buf;
  pclose(pp);
  return (char*)(result->c_str());
}

// gpg::recvPubKey
// Description - PubKeyID에 해당하는 PublicKey를 keyserver로부터 받는 gpg --recv-key를 수행(fork-exec) 사용
// Return - True(성공), False(실패)
bool gpg::recvPubKey(string* PubKeyID){
  string prefix_cmd("gpg --no-tty --batch --logger-fd 1 --recv-keys ");
  string suffix_cmd(" 2>/dev/null");

  // checking PUBKEYID
  if(PubKeyID->size()!=8){
    cout << "Length Fault" << endl;
    cout << PubKeyID->size() << endl;
    return false;
  }
  else if(not(std::regex_match(*PubKeyID, std::regex("[0-9|A-F]*")))){
    cout << "REGEX Fault" << endl;
    cout << (std::regex_match(*PubKeyID, std::regex("[0-9|A-F]*"))) << endl;
    return false;
  }


  string full_cmd(prefix_cmd+*PubKeyID+suffix_cmd);

  char* buf = new char[1024];
  FILE* pp = popen(full_cmd.c_str(),"r");
  string* result = NULL;
  if(pp==NULL){
    cout << "Fail to exec gpg" << endl;
    return false;
  }
  while(fgets(buf,1024,pp)){
    if(result==NULL){
      result = new string(buf);
    }
    else{
      result->append(buf);
    }
  }

  if(not(result->find("gpg: Total number processed: 1")!=std::string::npos)){
    return false;
  }
  delete buf;
  delete result;
  pclose(pp);
  return true;
}
