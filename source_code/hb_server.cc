#include "hb_server.hh"
#include "parser.hh"
#include "gpg.hh"
#include <unistd.h>

// hbchecker::setOneTimeKey
// Description - 생성된 OneTimeKey를 할당
// return - 없음
void hbchecker::setOneTimeKey(char* OTK) {
	std::ifstream urand("/dev/urandom");
  urand.read(OTK, 4);
  urand.close();
}

void* hbchecker::hbCheckerMain(void* args){
	while(true){
		// pthread_mutex_lock(&m_node_list);
		// vector<string>* id_list = node_list.getGithubIDList();
		// pthread_mutex_unlock(&m_node_list);

	 //  for(std::vector<string>::iterator it = id_list->begin() ; it != id_list->end(); ++it){
	 //    pthread_mutex_lock(&m_node_list);
	 //    node* _node = node_list.searchNode(*it, 0);
	 //    pthread_mutex_unlock(&m_node_list);
	 //    if(_node != NULL){
	 //    	char OTK[4];
	 //    	char stream[HB_LEN];
	 //    	hbchecker::setOneTimeKey(OTK);
	 //    	parser::packHeartBeat(stream, OTK);

	 //    }

	 //    char stream[MAX_LEN];
	 //    int length = parser::packNode(stream, _node, SIGN_IN);
	 //    // char* encStream =  gpg::encBytestream(stream, &pubKeyID, length);

	 //    char* encStream = gpg::encBytestream(stream, &pubKeyID);
	 //    struct tmd::arg_data* list_update_arguments = new struct tmd::arg_data();
	 //    tmd::data_args(_node->getIP(), encStream, list_update_arguments);
	 //    delete encStream;

	 //    pthread_t th_list_update;
	 //    pthread_create(&th_list_update, NULL, tmd::tmdSender, (void*)list_update_arguments);
	    
	 //  }
	 //  delete id_list;

		sleep(5);
	}
	
}

// // hbchecker::setTimestamp
// // Description - 생성된 Timestamp를 할당
// // return - 없음
// void hbchecker::setTimestamp(time_t _Timestamp) {
// 	timestamp = _Timestamp;
// }


// // hbchecker::hbchecker
// // Description - Server에서 Heartbeat를 위한 초기 소켓 할당
// // return - 없음 
// hbchecker::hbchecker(char* _OneTimeKey, time_t _Timestamp)
// {
// 	int err;

// 	try{
// 		serv_fd = socket(AF_INET, SOCK_DGRAM, 0);
// 		if (serv_fd < 0)
// 			throw 1;

// 		memset( &serv_addr, 0, sizeof(serv_addr));

// 		serv_addr.sin_family		= AF_INET;
// 		serv_addr.sin_port 		= htons(HB_PORT);
// 		serv_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	
// 		if (bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
// 			throw 3;

// 		cout << "[=] HB function Activated" << endl;

// 	} 
// 	catch(int except){
// 		cout << (except == 1? "Sock":"Bind")  << "erorr occured!" << endl;
// 		return;
// 	}
// }

// // hbchecker::getOneTimeKey
// // Description - OneTimeKey를 출력
// // return - (char*)OneTimeKey
// char* hbchecker::getOneTimeKey() {
// 	return OneTimeKey;
// }

// // hbchecker::getTimestamp
// // Description - timestamp
// // return - (time_t)timestamp
// time_t hbchecker::getTimestamp() {
// 	return timestamp;
// }


// // hbchecker::recvHB
// // Description - Heartbeat 수신부 생성
// // return - True or False
// bool hbchecker::recvHB()
// {
// 	if (serv_fd < 1)
// 		throw false;
// 	try {
// 		sockaddr_in send_addr;
// 		int msglen;
// 		int send_addrlen;
// 	        int recv_err;
// 		char buf[MAXSENDBUFSIZE]; 
	
// 		while(true) {
// 			send_addrlen = sizeof(send_addr);
// 			msglen = recvfrom(serv_fd, buf, MAXRECEIVEBUFSIZE, 0, (struct sockaddr*)&send_addr, (socklen_t*)&send_addrlen);
// 			buf[msglen] = '\0';
// 			cout << "[UDP/" << inet_ntoa(send_addr.sin_addr) << ":" << ntohs(send_addr.sin_port) << "]" << endl;
// 		}
// 	} catch(bool except) {
// 		cout << "Initialization of the socket is needed!" << endl;
// 		close(serv_fd);
// 		return false;
// 	}
// 	close(serv_fd);
// 	return true;
// }

// // hbchecker::sendHB
// // Description - Heartbeat 메시지 미도착시 사용(송신 주소, 송신할 메시지)
// // return - True or False
// bool hbchecker::sendHB(char* hb_addr, char* send_msg)
// {
// 	int send_fd;
// 	try {
// 		send_fd = socket(AF_INET, SOCK_DGRAM, 0);
// 		if ( send_fd < 0 )
// 			throw send_fd;

// 		struct sockaddr_in send_addr;
// 		memset( &send_addr, 0, sizeof(send_addr) );
// 		send_addr.sin_family		= AF_INET;
// 		send_addr.sin_port		= htons(HB_PORT);
// 		send_addr.sin_addr.s_addr	= inet_addr(hb_addr);

// 		sendto(send_fd, send_msg, strlen(send_msg) + 1, 0, (struct sockaddr*)&send_addr, sizeof(send_addr));
// 	} catch(int except) {
// 		cout << "[!] Send error!" << endl;
// 		close( send_fd );
// 		return false;
// 	}

// 	cout << "[=] Send Complete! Wait for HB Signal.." << endl;

// 	close( send_fd );	
// 	return true;
// }
