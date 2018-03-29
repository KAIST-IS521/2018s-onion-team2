#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
  cout << to_string(inet_addr("143.248.249.111")) << endl;
  return 0;
}
