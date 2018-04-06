#include "ui.hh"

using namespace std;

// Original code for this function can be found on https://gist.github.com/wewearglasses/2521037
string ui::getIPAddr(){
  string ip_addr = "";
  struct ifaddrs* net_ifa = NULL;
  struct ifaddrs* cur_ifa = NULL;

  if(!getifaddrs(&net_ifa)){
    cur_ifa = net_ifa;
    while(cur_ifa) {
      // if(cur_ifa->ifa_addr->sa_family == AF_INET && cur_ifa->ifa_name == string("eth0")) {
      if(cur_ifa->ifa_addr->sa_family == AF_INET && cur_ifa->ifa_name == string("enp0s31f6")) {
        ip_addr = inet_ntoa(((struct sockaddr_in*)cur_ifa->ifa_addr)->sin_addr);
      }
      cur_ifa = cur_ifa->ifa_next;
    }
  }

  if(!net_ifa)
    freeifaddrs(net_ifa);
  return ip_addr;
}

void ui::clearScreen()
{
  cout << "\e[1;1H\e[2J";
}

void ui::printBanner(){
  cout << " /$$     /$$                                     " << endl;
  cout << "|  $$   /$$/                                     " << endl;
  cout << " \\  $$ /$$//$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$ " << endl;
  cout << "  \\  $$$$//$$__  $$| $$  | $$| $$__  $$ /$$__  $$" << endl;
  cout << "   \\  $$/| $$  \\ $$| $$  | $$| $$  \\ $$| $$  \\ $$" << endl;
  cout << "    | $$ | $$  | $$| $$  | $$| $$  | $$| $$  | $$" << endl;
  cout << "    | $$ |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$$" << endl;
  cout << "    |__/  \\______/  \\______/ |__/  |__/ \\____  $$" << endl;
  cout << "                                        /$$  \\ $$" << endl;
  cout << "                                       |  $$$$$$/" << endl;
  cout << "                                        \\______/ " << endl;
  cout << " /$$      /$$ /$$$$$$$$                                                                     " << endl;
  cout << "| $$$    /$$$| $$_____/                                                                     " << endl;
  cout << "| $$$$  /$$$$| $$        /$$$$$$$ /$$$$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ " << endl;
  cout << "| $$ $$/$$ $$| $$$$$    /$$_____//$$_____/ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$" << endl;
  cout << "| $$  $$$| $$| $$__/   |  $$$$$$|  $$$$$$ | $$$$$$$$| $$  \\ $$| $$  \\ $$| $$$$$$$$| $$  \\__/" << endl;
  cout << "| $$\\  $ | $$| $$       \\____  $$\\____  $$| $$_____/| $$  | $$| $$  | $$| $$_____/| $$      " << endl;
  cout << "| $$ \\/  | $$| $$$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$| $$      " << endl;
  cout << "|__/     |__/|________/|_______/|_______/  \\_______/|__/  |__/ \\____  $$ \\_______/|__/      " << endl;
  cout << "                                                               /$$  \\ $$                    " << endl;
  cout << "                                                              |  $$$$$$/                    " << endl;
  cout << "                                                               \\______/                     " << endl;
}

userInfo ui::login(){
  string GithubId, PubKeyID, IP, Passphrase;
  ui::clearScreen();
  ui::printBanner();
  cout << "> Github ID: ";
  cin >> GithubId;
  cout << "> Public key ID: ";
  cin >> PubKeyID;
  Passphrase = getpass("> Passphrase: ");

  if(GithubId.length() > 40) {
    cout << "[!] Your Github ID is too long";
    exit(-1);
  } else if((IP = ui::getIPAddr()) == "") {
    cout << "[!] Error in retrieving the ip address";
    exit(-1);
  }

  return userInfo(GithubId, PubKeyID, IP, Passphrase);
}

void* ui::userInput(void* args){
  string userInput;
  while(true){
    cin >> userInput;
    cout << userInput << endl;
  }
  return NULL;
}
