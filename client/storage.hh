#ifndef __storage__
#define __storage__

class storage{
private:
  string path;
public:
  storage(string path);
  bool storeMessage(message* target);
  int storeMessage(list<message> messageList);
  list<message> loadMessage(string GithubID);
  list<message> loadMessage(string GithubID, int count);
  
  //List는 봐서.. 저장을..
}

#endif
