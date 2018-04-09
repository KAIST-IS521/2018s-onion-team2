#include "ui.hh"
#include "gpg.hh"
#include <iomanip>

using namespace std;

//enum {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE};

// Original code for this function can be found on https://gist.github.com/wewearglasses/2521037
string ui::getIPAddr(){
  string ip_addr = "";
  struct ifaddrs* net_ifa = NULL;
  struct ifaddrs* cur_ifa = NULL;

  if(!getifaddrs(&net_ifa)){
    cur_ifa = net_ifa;
    while(cur_ifa) {
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
  cout << endl;
  cout << setw(70) <<  " /$$     /$$                                     " << endl;
  cout << setw(70) << "|  $$   /$$/                                     " << endl;
  cout << setw(70) << " \\  $$ /$$//$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$ " << endl;
  cout << setw(70) << "  \\  $$$$//$$__  $$| $$  | $$| $$__  $$ /$$__  $$" << endl;
  cout << setw(70) << "   \\  $$/| $$  \\ $$| $$  | $$| $$  \\ $$| $$  \\ $$" << endl;
  cout << setw(70) << "    | $$ | $$  | $$| $$  | $$| $$  | $$| $$  | $$" << endl;
  cout << setw(70) << "    | $$ |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$$" << endl;
  cout << setw(70) << "    |__/  \\______/  \\______/ |__/  |__/ \\____  $$" << endl;
  cout << setw(70) << "                                        /$$  \\ $$" << endl;
  cout << setw(70) << "                                       |  $$$$$$/" << endl;
  cout << setw(70) << "                                        \\______/ " << endl;
  cout << setw(100) << " /$$      /$$ /$$$$$$$$                                                                     " << endl;
  cout << setw(100) << "| $$$    /$$$| $$_____/                                                                     " << endl;
  cout << setw(100) << "| $$$$  /$$$$| $$        /$$$$$$$ /$$$$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ " << endl;
  cout << setw(100) << "| $$ $$/$$ $$| $$$$$    /$$_____//$$_____/ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$" << endl;
  cout << setw(100) << "| $$  $$$| $$| $$__/   |  $$$$$$|  $$$$$$ | $$$$$$$$| $$  \\ $$| $$  \\ $$| $$$$$$$$| $$  \\__/" << endl;
  cout << setw(100) << "| $$\\  $ | $$| $$       \\____  $$\\____  $$| $$_____/| $$  | $$| $$  | $$| $$_____/| $$      " << endl;
  cout << setw(100) << "| $$ \\/  | $$| $$$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$| $$      " << endl;
  cout << setw(100) << "|__/     |__/|________/|_______/|_______/  \\_______/|__/  |__/ \\____  $$ \\_______/|__/      " << endl;
  cout << setw(100) << "                                                               /$$  \\ $$                    " << endl;
  cout << setw(100) << "                                                              |  $$$$$$/                    " << endl;
  cout << setw(100) << "                                                               \\______/                     " << endl;
  cout << setw(280) << "                                                                                     V 1.0   " << endl;
  cout << endl;
}

userInfo ui::login(nodelist* node_list){
  string GithubId, PubKeyID, IP, Passphrase;
  while(1) {
      int err_detect[3] = {1,1,1};
      char err;

      ui::clearScreen();
      ui::printBanner();

      cout << endl;
      cout << setw(50) << "\x1b[32m >> Github ID : ";
      GithubId = inputCheck();


      if(GithubId.size() >= 40) {
        cout << "[!] Your Github ID is too long" << endl;
        err = cin.get();
        continue;
      }
      else if (GithubId.size() < 2) {
        cout << "[!] Must typing in this section";
        err = getchar();
        continue;
      }
      else if ((node_list->searchNode(GithubId,0) == NULL) || (node_list->searchNode(util::getContainerIP(),1) != node_list->searchNode(GithubId,0))){
        cout << "[!] No Registed User";
        err = getchar();
        continue;
      } else {
        err_detect[0] = 0;
      }

      cout << setw(54) << "\x1b[34m >> Public key ID : ";
      PubKeyID = inputCheck();

      cout << setw(50) << "\x1b[35m >> Passphrases:";
      Passphrase = getpass("");
      
      char* encPassOTK;
      char* decPassOTK;
      char *passOTK = new char[5];
      bzero(passOTK, 5);
      ifstream urand("/dev/urandom");
      urand.read(passOTK, 4);
      urand.close();
      try{
      encPassOTK = gpg::encBytestream(passOTK, &PubKeyID, 4);
      if(encPassOTK == NULL)
        throw 1;
      decPassOTK = gpg::decBytestream(encPassOTK, &Passphrase);
      if(decPassOTK == NULL)
        throw 2;
      else if(Passphrase.compare("")==0 || strncmp(decPassOTK,passOTK,4) ) {
        cout << "[!] ERROR Passpharase" << endl;
        err_detect[2] = 1;
      }
      else{
        err_detect[2] = 0;
      }
      }
      catch(int exception){
        delete(passOTK);
        if(exception == 2)
          delete(encPassOTK);
        continue;
      }
      delete(passOTK);
      delete(encPassOTK);
      delete(decPassOTK);

      if( (err_detect[0] + err_detect[2]) == 0 ) {
        cout << "\x1b[0m" << endl;
        break;
      }

      ui::clearScreen();
  }

  cout << setw(70) << "Login Confirmed! PRESS ANY KEY..." << endl;
  return userInfo(GithubId, PubKeyID, IP, Passphrase);
}

string ui::inputCheck() {
    string result_input("");
    
    while(1) {
        char ichar = cin.get();
        string string_input ( 1, ichar );

        if(( ichar == 0x7f || ichar == 8 )&&result_input.empty() == false ) {
            cout << "\xb";
            cout << " ";
            cout << "\xb";
            result_input.pop_back();
            continue;
        }


        if( ichar == '\x0a' ) {
            return result_input;
        }
        else {
            result_input.append( string_input );
        }

        fflush(stdout);
    }
    return NULL;
}

void* ui::userInput(void* args){
  string userInput;
  while(true){
    cin >> userInput;
    cout << userInput << endl;
  }
  return NULL;
}
