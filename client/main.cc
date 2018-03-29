#include <iostream>
#include "ui.hh"
#include "userInfo.hh"
using namespace std;

int main(int argc, char const *argv[])
{
  userInfo user = ui::login();
  ui::printBanner(user);
  return 0;
}