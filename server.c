#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define bufferSize 1024

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	int i, strLen;
	char msg[bufferSize];
	
	if(argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(0);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("WSAStartup() error");
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(argv[1]));
	
	serverSock = socket(PF_INET, SOCK_STREAM, 0);
	if(serverSock == INVALID_SOCKET) {
		perror("socket() error");
	}
	
	if(bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		perror("bind() error");
	}
	
	if(listen(serverSock, 5) == SOCKET_ERROR) {
		perror("listen() error");
	}
	
	clientAddrSize = sizeof(clientAddr);
	for(i = 0; i < 5; i++) {
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if(clientSock == -1) {
			perror("accept() error");
		} else {
			printf("Connected! \n");
		}
		
		while((strLen = recv(clientSock, msg, bufferSize, 0)) != 0) {
			printf("receive to client : %s \n", msg);
			send(clientSock, msg, strLen, 0);
		}
		
		closesocket(clientSock);
	}
	
	closesocket(serverSock);
	WSACleanup();
	return 0;
}
