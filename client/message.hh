
#ifndef __MESSAGE__
#define __MESSAGE__

class encMessage{
private:
  string nextIP;
  char* encData;
publlic:
  encMessage();
  string getNextIP();
  char* getEncData();
  bool setNextIP(string src);
  bool setEncData(char* src);
 };

class message{
private:
  string Content;
  string GithubID;
  char* OneTimeKey;
  time_t timestamp;
  bool writable;
public:
  message();
  bool setMessage();
  string getContents();
  string getGithubID();
  string getTimestamp();
  char* getOneTimeKey();
  bool isWriteable();
  bool setTimestamp(time_t timestamp);
  bool setGithubID(string githubID);
  bool setOneTimeKey(char* OneTimeKey);
  bool setContents(string content);
};

#endif
