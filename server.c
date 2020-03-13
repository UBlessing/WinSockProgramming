#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define bufferSize 1024

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET connectSock;
	SOCKADDR_IN serverAddr;
	int strLen;
	char msg[bufferSize];
	
	if(argc != 3) {
		printf("Usage: %s <ip> <port> \n");
		exit(0);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		perror("WSAStartup() error");
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(atoi(argv[2]));
	
	connectSock = socket(PF_INET, SOCK_STREAM, 0);
	if(connectSock == INVALID_SOCKET) {
		perror("socket() error");
	}
	
	if(connect(connectSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		perror("connect() error");
	} else {
		printf("Connected! \n");
	}
	
	fputs("('exit' to quit)>", stdout);
	fgets(msg, bufferSize, stdin);
		
	if(!strcmp(msg, "exit\n")) {
		printf("Exit! \n");
		closesocket(connectSock);
		WSACleanup();
		return 0;
	}
		
	send(connectSock, msg, bufferSize, 0);
	while((strLen = recv(connectSock, msg, bufferSize, 0)) != 0) {
		msg[strLen] = '\0';
		printf("Mssage from server : %s \n", msg);
		
		fputs("('exit' to quit)>", stdout);
		fgets(msg, bufferSize, stdin);
		
		if(!strcmp(msg, "exit\n")) {
			printf("Exit! \n");
			break;
		}
		
		send(connectSock, msg, bufferSize, 0);
	}
	
	closesocket(connectSock);
	WSACleanup();
	return 0;
}
