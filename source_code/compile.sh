g++ client_main.cc util.cc ui.cc userInfo.cc nodelist.cc transmission.cc heartbeat.cc timestamp.cc parser.cc gpg.cc -o client -lpthread -std=c++11
g++ server_main.cc list_check.cc util.cc nodelist.cc parser.cc timestamp.cc gpg.cc transmission.cc userInfo.cc -o server -lpthread -std=c++11

