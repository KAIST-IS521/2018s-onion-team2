#ifndef __HBCHECKER_HH__
#define __HBCHECKER_HH__
#include "util.hh"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>

// #define HB_PORT			60000
// #define BYTE			unsigned char
// #define BUFF_SIZE		1024
// #define MAXCONNECTIONS		5
// #define MAXSENDBUFSIZE		1023
// #define	MAXRECEIVEBUFSIZE	1024
// #define MAXWAITBUFSIZE		4096	

// #define	HBHDR_FLAG		0x04
// #define HBHDR_OTK		8
// #define HBHDR_TIME		4
// #define OTK_SIZE 4

// struct HB_HDR
// {
// 	unsigned char			flag;
// 	unsigned char		 	otk[HBHDR_OTK];
// 	unsigned int			timestamp;
// };


// using namespace std;

namespace hbchecker{
  void setOneTimeKey(char* OTK);
  void* hbCheckerMain(void* args);
};

// class hbchecker {
// private:
//   sockaddr_in serv_addr;
//   char OneTimeKey[OTK_SIZE];
//   time_t timestamp;
//   int serv_fd;
// public:
//   hbchecker(char* _OneTimeKey, time_t _Timestamp);
//   char*		getOneTimeKey();
//   time_t	getTimestamp();
//   void		setTempinfo(char* _OneTimeKey, time_t _timestamp);
//   void		setOneTimeKey(char* _OneTimeKey);
//   void		setTimestamp(time_t _Timestamp);
//   bool 		recvHB();
//   bool 		sendHB(char* hb_addr, char* send_msg);
// };
#endif
