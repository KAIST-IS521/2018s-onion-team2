#include "transmission.hh"
#include <iostream>

pthread_mutex_t	trd_switch	= PTHREAD_MUTEX_INITIALIZER;

// tmd::tmdReceiver
// Description - tmdReceiverMain에서 Thread로 나눌 함수, Port를 지속적으로 Listen하고 있음
// Return - 0(정상종료) or 음수
void* tmd::tmdReceiver(void* recvfd){
	char* buf;
	char* temp_Buf	= new char[CURRENTBUFSIZE];
	int curbuf_idx = 0;
	int streamsize	= CURRENTBUFSIZE;
	int recvfd	= *(int*)_recvfd;
	string passwd	= 'abcdfasdfa';
	
	char* new_Buf;
	

	pthread_detach(pthread_self());

	try{
		while(read(recvfd, temp_Buf, CURRENTBUFSIZE)) {
			if(curbuf_idx == 0) {
				buf = new char[CURRENTBUFSIZE];
				strncpy(buf, temp_Buf, CURRENTBUFSIZE);  // 변경필요
				memcpy(temp_Buf, 0, CURRENTBUFSIZE);
				curbuf_idx = 1024;
			} 
			else {
				new_Buf = new char[currnet_Buf + CURRENTBUFSIZE];
				memset(new_Buf, 0, curbuf_idx + CURRENTBUFSIZE);
				strncpy(new_Buf, buf, curbuf_idx);
				strncat(new_Buf, temp_Buf, CURRENTBUFSIZE);
				memcpy(temp_Buf, 0, CURRENTBUFSIZE);
				curbuf_idx += CURRENTBUFSIZE;
				delete[] buf;
				buf = new_Buf;
			}
		}
	} catch (int exceptionCode) {
		// None
	}
	// return buf
	// processing recived packet

	buf  = tmdReciver(recvfd);

	// decrypt buf by pubkey
	string passphrase(passwd);
	buf = gpg::decBytestream(buf, passphrase);
	switch(buf[0]) {
		// 0x04(heartbeat) 여기서는 처리하면 안됨
		// MUTEX에 대한 주의 필요(?)
		// Critical Section에 대한 처리
		// pthread_mutex_lock(&trd_switch)
		// pthread_mutex_unlock(&trd_switch)
		case '\x00':
			// 평문 : message 객체로 만들고, storage(sql_lite) 저장
			break;
		case '\x01':
			// 암호문 : 길이 및 메시지 따서 해당 서버로 재송신
			break;
		case '\x02':
			// 리스트 업데이트 : 프로토콜에 맞게 파싱하여 리스트 추가 및 삭제
			break;
		defalut:
			// fail : 이 외에는 받아들이지 않아야하는 데이터이므로 무시
			break;
	}
	return 0;
}

// tmd::tmdReceiverMain
// Description - 지속적으로 tmdReceiver 함수를 구동. tmdReceiver에서 반환한 char STREAM을 처리하고 계속 무한루프.
// Return - 0(정상 종료), -1(이상 종료)
int tmd::tmdReceiverMain() {
	char* buf;
	int recvfd;
	int sockfd	= socket(AF_INET, SOCK_STREAM, 0);
	
	pthread_t tid[MAX_THREAD];
	if(sockfd < 0){
		return -1;
	}

	struct sockaddr_in	sock_info, conn_info;
	int conn_len	= sizeof(conn_info);
	memset((char*)&sock_info, 0, sizeof(sock_info));
	sock_info.sin_family		= AF_INET;
	sock_info.sin_addr.s_addr 	= INADDR_ANY;
	sock_info.sin_port		= htons(MESSAGE_PORT);

	if (0 > bind(sockfd, (struct sockaddr*)&sock_info, sizeof(sock_info))) {
		cout << "bind error!" << endl;
		return -2;
	};

	if (0 > listen(sockfd, 10)) {
		cout << "listen error" << endl;
		return -3;
	}

	while(true) {
		for (int i = 0; i<MAX_THREAD; i++) {
			recvfd = accept(sockfd, (struct sockaddr*)&conn_info, (socklen_t*));
			cout << recvfd << endl;
			if (recvfd<0) {
				return -4;
			}
			pthread_create(&tid[i], NULL, tmdReceiver, (void **)&recvfd);
		}
	}
	return 0;
}

// tmd::tmdPathSelector
// Description - 타 클라이언트 메시지 전송시 Path를 결정. nodes만큼의 클라이언트를 거치도록 만들어줌
// Return - IP 배열 or Null(실패)
list <node*> tmd::tmdPathSelector(int nodes) {
	return nodelist::getRandomNode(nodes - 1);
}

// tmd::tmdPackPacket
// Description - 평문 char stream을 송신자와 Path 순서대로 암호화한다.
// Return - character(Encrypted) or Null(실패)
char* tmd::tmdPackPacket(node* sender, node* receiver, char* plain) {
	list <node*> pathlist = tmd::tmdPathSelector(MAX_PATH);
	// 현재 최대 Encrypt path는 3개
	if(pathlist.size() < 3) {
		return NULL;
	}

	char* encPr = gpg::encBytestream(plain, receiver->node::getPubKeyID());

	// pathlist : receiver -> B -> C 순서
	// Encrypt 순서 : C -> B -> receiver
	pathlist.insert(pathlist.begin(), receiver);

	// encPr = Erec(Prec)
	// structure : EC(EB(encPr, Erec)EB)
	list <node*> iterator i = pathlist.begin();
	while(i != pathlist.end()) {
		encPr = gpg::endBytestream(parser::packEncMessage(encPr, *(i)->getIP()), *(i+1)->getPubKeyID());
		i++;
	}
	return encPr;
}

// tmd::tmdSender
// Description - char stream을 특정 IP로 전송함
// Return - True(성공) or False(실패)
bool tmd::tmdSender(string IP, char* scheme, int scheme_len) {
	char* buf;
	int recvfd;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0) {
		return -1;
	}

	struct sockaddr_in sock_info, conn_info;
	int conn_len = sizeof(conn_info);
	memset((char *)&sock_info, 0, sizeof(sock_info));
	sock_info.sin_family		= AF_INET;
	sock_info.sin_addr.s_addr 	= inet_addr(IP.c_str());
	sock_info.sin_port		= htons(MESSAGE_PORT);

	if( 0 > connect(sockfd, (struct sockaddr*)&sock_info, sizeof(sock_info))) {
		return -2;
	}

	if( 0 > send(sockfd, scheme, scheme_len, 0) {
		return -3;
	}
	close(sockfd);
	return 0;
}
