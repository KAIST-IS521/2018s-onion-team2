
#ifndef __MESSAGE__
#define __MESSAGE__

class encMessage{
private:
  string nextIP;
  string encData;
publlic:
  encMessage();
  string getNextIP();
  string getEncData();
  bool setNextIP(string src);
  bool setEncData(string src);
 }

class message{
private:
  string Content;
  string GithubID;
  char* OneTimeKey;
  time_t timestamp;
  bool writable;
public:
  message();
  message(string _content,string _GithubID, char* _OneTimeKey, time_t _timestamp);
  string getContents();
  string getGithubID();
  string getTimestamp();
  char* getOneTimeKey();
  bool isWriteable();
  bool setTimestamp(time_t timestamp);
  bool setGithubID(string githubID);
  bool setOneTimeKey(char* OneTimeKey);
  bool setContents(string content);
}

#endif
