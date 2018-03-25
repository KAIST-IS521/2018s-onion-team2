#include <iostream>
#include "ui.hh"
#include "userInfo.hh"
#include "hearbeat.hh"

using namespace std;

userInfo ui::login(){
  string GithubId, PublicKeyID, IP, Passphrase;
  clearScreen();
  cout << "Please enter your Github ID: ";
  cin >> GithubId;
  cout << "Please enter your public key ID: ";
  cin >> PublicKeyID;
  cout << "Please enter passphrase: ";
  cin >> Passphrase;

  // We may need to change the code to automatically detect user's ip address
  cout << "Please enter your IP address: ";
  cin >> IP;

  // Send an info that user has logged-in to the server

  // Retrieve client list from the Server

  // Create a thread for the listening

  return userInfo(GithubId, PublicKeyID, IP, Passphrase);
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
    cout << /*[node_idx] user githubID : N new messages*/ << endl;

  cout << "Select the one you want to chat with: ";
  cin >> /* githubID */;
  printMessages(githubID);
}