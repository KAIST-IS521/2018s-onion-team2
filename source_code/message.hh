#ifndef __MESSAGE__
#define __MESSAGE__

#include <string>
#include <ctime>
#include <iostream>

using namespace std;

class encMessage{
private:
  string nextIP;
  string encData;
public:
  encMessage();
  string getNextIP();
  string getEncData();
  bool setNextIP(string src);
  bool setEncData(string src);
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
  message(string _content,string _GithubID, char* _OneTimeKey, time_t _timestamp);
  ~message();
  string getContents();
  string getGithubID();
  time_t getTimestamp();
  char* getOneTimeKey();
  bool isWritable();
  bool setTimestamp(time_t timestamp);
  bool setGithubID(string githubID);
  bool setOneTimeKey();
  bool setContents(string content);
};

#endif
