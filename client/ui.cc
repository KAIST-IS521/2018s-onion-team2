#include <iostream>
#include "ui.hh"
#include "userInfo.hh"

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
	cout << "Welcome to Onion Messanger, " + user.getGithubID() + "!!!" << endl;
}