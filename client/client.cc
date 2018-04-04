#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

void printHelp(char* const argv[]){
  cout << "Usage: " + string(argv[0]) + " -p [PORT] -m [MESSAGE]" << endl;
  exit(0);
};

int main(int argc, char* const argv[]){
  int opt;
  int port = -1;
  string message = "";
  
  while((opt = getopt(argc, argv, "p:m:h")) != -1){
    switch(opt){
      case 'p':
        // Set a port
        port = atoi(optarg);
        break;
      case 'm':
        // Set a message
        message = optarg;
        break;
      case 'h':
        // Print help message
        printHelp(argv);
        break;
    }
  }
  
  // Wrong use of arguments
  if(port == -1 || message == "") {
    printHelp(argv);
    return 1;
  }

  return 0;
}
