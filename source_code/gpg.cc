#include "gpg.hh"

using namespace gpg;

/* Referenced - http://fm4dd.com/programming/base64/base64_stringencode_c.htm */
/* Modified by hexife */
char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/* encodeblock - encode 3 8-bit binary bytes as 4 '6-bit' characters */
string encodeblock(unsigned char in[],int len) {
    char* out = new char[5];
    out[0] = b64[ in[0] >> 2 ];
    out[1] = b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? b64[ ((in[1] & 0x0f) << 2) |
             ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    string ret_str(out);
    delete out;
    return ret_str;
}

/* encode - base64 encode a stream, adding padding if needed */
void b64_encode(char *clrstr,string* b64dst,int length) {
  unsigned char in[3];
  int i, len = 0;
  int j = 0;

  //b64dst[0] = '\0';
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
      b64dst->append(encodeblock( in , len));
    }
  }
}


// gpg::encBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg encryption을 수행하고 결과를 반환
// Return - Encrypted Byte* or Null(실패 시)
char* gpg::encBytestream(char* src,string* PubKeyID,int length){
  string prefix_cmd("echo \"");
  string middle_cmd("\" | base64 -d | gpg --no-tty --batch --logger-fd 1 --always-trust -ear ");
  string suffix_cmd(" 2>/dev/null");

  std::regex exp ("[0-9|A-F]*");

  // checking PUBKEYID
  if(PubKeyID->size()!=8){
    cout << "Public Key ID Length Fault" << endl;
    return NULL;
  }
  else if(not(std::regex_match(*PubKeyID, exp))){
    cout << "Public Key ID REGEX Fault" << endl;
    return NULL;
  }
  int count = 0;

  string base64_dst("");
  b64_encode(src,&base64_dst, length+count);
  string full_cmd(prefix_cmd+base64_dst+middle_cmd+*PubKeyID+suffix_cmd);
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
  char* encResult = new char[result->size()+1];
  memcpy(encResult, result->c_str(), result->size());
  delete result;
  return encResult;
}

// gpg::decBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg decription을 수행하고 결과를 반환
// Return - Plain char* or Null(실패 시)
char* gpg::decBytestream(char* src, string* passphrase){
  string encData(src);
  string prefix_cmd("echo \'");
  string middle_cmd("\' | gpg --no-tty --batch --logger-fd 1 -d --passphrase \'");
  string suffix_cmd("\' 2>/dev/null");
  // Add new exp ', >, <, &
  std::regex exp ("[;|\$\(|\)|\'|\>|\<|\&|\||\`]");
   if(std::regex_search(*passphrase,exp )){
    cout << "Passphrase REGEX Fault" << endl;
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
  char* decResult = new char[result->size()+1];
  bzero(decResult, result->size()+1);
  memcpy(decResult, result->c_str(), result->size());
  delete result;
  return decResult;
}
