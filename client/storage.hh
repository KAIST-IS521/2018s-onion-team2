#ifndef __storage__
#define __storage__

class storage{
private:
  String path;
public:
  storage(String path);
  bool storeMessage(message* target);
  int storeMessage(list<message> messageList);
  list<message> loadMessage(String GithubID);
  list<message> loadMessage(String GithubID, int count);
  
  //List는 봐서.. 저장을..
}

#endif
