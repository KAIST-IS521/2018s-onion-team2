
#ifndef __MESSAGE__
#define __MESSAGE__

class encMessage{
private:
  String nextIP;
  BYTE* encData;
publlic:
  encMessage();
  String getNextIP();
  BYTE* getEncData();
  bool setNextIP(String src);
  bool setEncData(BYTE* src);
 }

class message{
private:
  String Content;
  String GithubID;
  BYTE* OneTimeKey;
  long timestamp;
  bool writable;
public:
  message();
  bool setMessage();
  String getContents();
  String getGithubID();
  String getTimestamp();
  BYTE* getOneTimeKey();
  bool isWriteable();
  bool setTimestamp(long timestamp);
  bool setGithubID(String githubID);
  bool setOneTimeKey(BYTE* OneTimeKey);
  bool setContents(String content);
}

#endif
