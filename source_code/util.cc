#include "util.hh"

pthread_mutex_t m_node_list = PTHREAD_MUTEX_INITIALIZER;
nodelist node_list;
userInfo user;
pthread_mutex_t m_user = PTHREAD_MUTEX_INITIALIZER;

string util::getContainerIP(){
   int    iSocket = -1;
   struct if_nameindex* pIndex = 0;
   struct if_nameindex* pIndex2 = 0;
   string tmpName;

   if ((iSocket = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
      return NULL;
   }

   pIndex = pIndex2 = if_nameindex();

   while ((pIndex != NULL) && (pIndex->if_name != NULL)){
      struct ifreq req;
      strncpy(req.ifr_name, pIndex->if_name, IFNAMSIZ);
      if (ioctl(iSocket, SIOCGIFADDR, &req) < 0){
         if (errno == EADDRNOTAVAIL){
            ++pIndex;
            continue;
         }
         close(iSocket);
         return NULL;
      }
      tmpName = inet_ntoa(((struct sockaddr_in*)&req.ifr_addr)->sin_addr);
      if(tmpName.compare("127.0.0.1")!=0){
        break;
      }
      ++pIndex;
   }
   close(iSocket);
   return tmpName;
}

void util::int2byte(int integer, char* byte){
  union util::int_byte x;
  x.integer = integer;
  memcpy(byte, x.byte, INT_SIZE);
}

int util::byte2int(char* integer){
  union util::int_byte x;
  memcpy(x.byte, integer, INT_SIZE);
  return x.integer;
}

void util::ip2byte(string IP, unsigned char* byte){
  int i = 0;
  char *ch = strtok((char*)IP.c_str(), ".");
  while (ch != NULL)
  {
    byte[i++]= atoi(ch);
    ch = strtok(NULL, ".");
  }
  assert(i == IP_SIZE);
}

string util::byte2ip(unsigned char* byte){
  string IP;
  for (int i = 0; i < IP_SIZE; ++i) {
    if(i != IP_SIZE-1)
      IP += to_string(byte[i]) + ".";
    else
      IP += to_string(byte[i]);
  }
  return IP;
}
