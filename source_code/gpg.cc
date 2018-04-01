#include "gpg.hh"

using namespace gpg;

// gpg::encBytestream
// Description - src의 char stream을 fork-exec를 통하여 gpg encryption을 수행하고 결과를 반환
// Return - Encrypted Byte* or Null(실패 시)
char* gpg::encBytestream(char* src, string* PubKeyID){
  string plain(src);
  string prefix_cmd("echo \"");
  string middle_cmd("\" | gpg --no-tty --batch --logger-fd 1 -ear ");
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

  // checking src (prevent cmd injection)
  for(int i=0;i<plain.size()-count;i++){
    if(src[i]=='\x22' and (i>0 and src[i-1]!='\x5c')){
      plain.replace(i+count,1,"\x5c\x22");
      count++;
    }
  }

  string full_cmd(prefix_cmd+plain+middle_cmd+*PubKeyID+suffix_cmd);

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
  cout << *result << endl;
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
  while(fgets(buf,1024,pp)){
    if(result==NULL){
      result = new string(buf);
    }
    else{
      result->append(buf);
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
  cout << *result << endl;

  if(not(result->find("gpg: Total number processed: 1")!=std::string::npos)){
    return false;
  }
  delete buf;
  delete result;
  pclose(pp);
  return true;
}

