#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#define pass ;
#define pause system("PAUSE")

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET connSock;
	SOCKADDR_IN serverAddr;
	
	char msg[11] = {0, };
	
	if(argc != 3) {
		printf("Usage: %s <ip> <port> \n", argv[0]);
		exit(0);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		perror("WSAStartup() Error");
		pause;
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(atoi(argv[2]));
	
	connSock = socket(PF_INET, SOCK_STREAM, 0);
	if(connSock == INVALID_SOCKET) {
		perror("socket() Error");
		pause;
	}
	
	if(connect(connSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		perror("connect() Error");
		pause;
	}
	
	recv(connSock, msg, sizeof(msg), 0);
	printf("receive to server : %s \n", msg);
	
	return 0;
}
