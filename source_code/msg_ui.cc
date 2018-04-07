#include "msg_ui.hh"

using namespace std;

list<string>* msgqueue = new list<string>();
string ibuffer ("");
string receiver ("");

void msg_ui::setDummyArgs(struct tmd::arg_data* send_args, string msg, nodelist* node_list, string recvID){//string path){
  list<string> ip_list;

  string senderIP = user.getIP(); // get ip code needs
  string receiverIP = (node_list->searchNode(recvID, 0))->getIP();
  int middle_nodes = 3; // changeable


  while(true){
    string tmp((node_list->getRandomNode())->getIP());
    if((ip_list.size()==0 && senderIP.compare(tmp)==0) or (ip_list.size()==middle_nodes-1 && receiverIP.compare(tmp)==0)){
      continue;
    }
    if(ip_list.size()!=0 && (ip_list.begin())->compare(tmp)==0){
      continue;
    }
    ip_list.push_front(tmp);
    if(ip_list.size() == middle_nodes){
      break;
    }
  }
  ip_list.push_front(receiverIP);

  // For the final client
  send_args->IP = ip_list.back();

  message _msg;
  _msg.setContents(msg);
  _msg.setGithubID(user.getGithubID());
  _msg.setOneTimeKey();
  _msg.setTimestamp(timestamp::getTimestampNow());

  // Convert the message into a protocol
  int stream_len = parser::getMessagePackLen(&_msg);
  char* stream = new char[stream_len];
  char* tmp_stream = stream;
  parser::packMessage(stream, &_msg, ip_list.front());


  // Encrypting the message
  node* node = node_list->searchNode(ip_list.front(), 1);
  string pubKeyId = node->getPubKeyID();
  stream = gpg::encBytestream(stream, &pubKeyId, stream_len);

  cout << "tmp_stream delete in"<< endl;
  delete tmp_stream;
  encMessage encMsg;
  for(list<string>::iterator it = ip_list.begin(); (++it)-- != ip_list.end(); it++){
    // For clients in the routing path excluding the final clients
    encMsg.setNextIP(*it);
    encMsg.setEncData(stream);
    delete stream;


    // Convert the message into a protocol
    stream_len = parser::getEncMessagePackLen(&encMsg);
    stream = new char[stream_len];
    parser::packEncMessage(stream, &encMsg);
    // Encrypting the message
    node = node_list->searchNode(*((++it)--), 1);
    pubKeyId = node->getPubKeyID();
    tmp_stream = stream;
    stream = gpg::encBytestream(stream, &pubKeyId, stream_len);
    cout << "tmp_stream delete in in loop"<< endl;
    delete tmp_stream;

  }

  send_args->length = string(stream).length();
  send_args->data = new char[send_args->length];
  memcpy(send_args->data, stream, send_args->length);
  delete stream;

}


int msg_ui::getBottomYLoc()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

void msg_ui::moveCursorLoc(int Y){
 printf("\033[%d;%dH", Y+1, 1);
 fflush(stdout);
}

void msg_ui::cmd_execute(string ibuffer){
  if(ibuffer.compare("/exit")==0){
    cout << "BYE!" << endl;
    exit(0);
  }
  else if(ibuffer.compare("/clear")==0){
    msgqueue->clear();
  }
  else if((ibuffer.substr(4)).compare("/to ")){
    receiver = ibuffer.substr(4,ibuffer.size()-4);
  }
}

void msg_ui::getRecvToMessageQueue(string you){
  pthread_mutex_lock(&m_user);
  message tmp = user.readMessage();
  
  while(!(tmp.getGithubID().size()==0)){
    string recvmsg(tmp.getGithubID()+" -> (YOU) "+you+" : "+tmp.getContents());
    cout << recvmsg << endl;
    msgqueue->push_back(recvmsg);
    tmp = user.readMessage();
  }
  pthread_mutex_unlock(&m_user);
}

void msg_ui::sendWrapper(string message, nodelist* node_list, string to){
  struct tmd::arg_data* send_args  = new struct tmd::arg_data();
  msg_ui::setDummyArgs(send_args, message, node_list, to);
  tmd::tmdSender(send_args);
}

void msg_ui::refresh_messages(string ibuffer,string senderID){
  fflush(stdout);
  system("clear"); // awful...
  msg_ui::getRecvToMessageQueue(senderID);
  for(std::list<string>::iterator i = msgqueue->begin();i != msgqueue->end();i++){
    cout << *i << endl;
  }
  msg_ui::moveCursorLoc(msg_ui::getBottomYLoc());
  cout << "[ "<< senderID <<" ]@YoungMEssenger>> (To. [ "<< receiver <<" ] ) :: "<< ibuffer; 
}

// Edited by elmisty
void* msg_ui::input_listener(void* args){
  int char_cnt = 0; // For limitation of the character
  //static struct termios	oldtio, newtio; // Using for Synchronous 

  struct msg_ui::arg_info* arguments = (struct msg_ui::arg_info*) args;
  string sender = arguments->senderID;
  nodelist* node_list = arguments->node_list;
  /*
  list<string>* msg_ui::msgqueue
  struct arg_data{
    string senderID;
    nodelist* node_list;
  }

  */

  //tcgetattr(0, &oldtio);
  //newtio = oldtio;
  //newtio.c_lflag &= ~ICANON; 
  //newtio.c_lflag &= ~ECHO;
  //tcsetattr(0, TCSANOW, &newtio);

  msg_ui::refresh_messages(ibuffer,sender);
  while(true){
    char ichar = getchar();
    string input_char (1,ichar);
    char_cnt++;
    if ( ichar == 27 ) {
      ichar = getchar();
      ichar = getchar();
      continue;
    }
    if(( ichar == 0x7f || ichar == 8) && ibuffer.empty() == false ) {
      printf("\b");
      printf(" ");
      printf("\b");
      ibuffer.pop_back();
      continue;
    }
    cout << input_char << endl;
    if(ichar == '\x0a'){
      if (ibuffer.c_str()[0] == '\x2f'){
        cmd_execute(ibuffer);
      }
      else{
        node* tmp = node_list->searchNode(receiver,0);
        if(tmp == NULL){
          cout << "No Receiever Setted.. use /to command" << endl;
          ibuffer.clear();
          continue;
        }
        else{
          string sendmsg(sender + " (YOU) -> "+receiver+" : "+ibuffer);
          msg_ui::sendWrapper(ibuffer, node_list, receiver);
          msgqueue->push_back(sendmsg);
        }
      }
      ibuffer.clear();
    }
    else{
      ibuffer.append(input_char);
    }
    msg_ui::refresh_messages(ibuffer,sender);
  }
}

