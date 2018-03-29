#include "ui.hh"
#include "userInfo.hh"
using namespace std;

int main(int argc, char const *argv[])
{
  userInfo user = ui::login();
  return 0;
}