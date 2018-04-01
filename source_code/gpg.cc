#include "gpg.hh"

using namespace gpg;

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static int mod_table[] = {0, 2, 1};

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char*)malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}


// gpg::encBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg encryption을 수행하고 결과를 반환
// Return - Encrypted Byte* or Null(실패 시)
char* gpg::encBytestream(char* src,string* PubKeyID,int length){
  string prefix_cmd("echo \"");
  string middle_cmd("\" | base64 -d | gpg --no-tty --batch --logger-fd 1 --always-trust -ear ");
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

  size_t b64size = 0;
  string full_cmd(prefix_cmd+base64_encode((unsigned char*)plain,length+count,&b64size)+middle_cmd+*PubKeyID+suffix_cmd);
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
