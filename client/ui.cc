#include "ui.hh"
#include "userInfo.hh"
#include "heartbeat.hh"
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

using namespace std;

// Original code for this function can be found on https://gist.github.com/wewearglasses/2521037
string ui::getIPAddr(){
  string ip_addr = "";
  struct ifaddrs* net_ifa = NULL;
  struct ifaddrs* cur_ifa = NULL;

  if(!getifaddrs(&net_ifa)){
    cur_ifa = net_ifa;
    while(cur_ifa) {
      if(cur_ifa->ifa_addr->sa_family == AF_INET && cur_ifa->ifa_name == string("docker0")) {
        ip_addr = inet_ntoa(((struct sockaddr_in*)cur_ifa->ifa_addr)->sin_addr);
      }
      cur_ifa = cur_ifa->ifa_next;
    }
  }

  if(!net_ifa)
    freeifaddrs(net_ifa);
  return ip_addr;
}

userInfo ui::login(){
  string GithubId, PubKeyID, IP, Passphrase;
  clearScreen();
  cout << "> Github ID: ";
  cin >> GithubId;
  cout << "> Public key ID: ";
  cin >> PublicKeyID;
  Passphrase = getpass("> Passphrase: ");

  if((IP = ui::getIPAddr()) == "") {
    cout << "[!] Error in retrieving the ip address";
    exit(-1);
  }

  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening

  return userInfo(GithubId, PubKeyID, IP, Passphrase);
}

void ui::clearScreen()
{
  cout << "\e[1;1H\e[2J";
}

// ui::printBanner
// Description - 프로그램 시작시 Banner를 띄워줌
// return - None
void ui::printBanner(userInfo user){
  clearScreen();
  string githubID;
  cout << "Welcome to Onion Messanger, " + user.getGithubID() + "!!!" << endl;

  // for node in node_list
  //  cout << /*[node_idx] user githubID : N new messages*/ << endl;

  cout << "Select the one you want to chat with: ";
  // cin >> /* githubID */;
  printMessages(githubID);
}

void ui::printMessages(string githubID){
  // for messages in the msg list, print messages

  // cin >> /* exit or send message */;
  // if exit => printBanner
  // else send message
}