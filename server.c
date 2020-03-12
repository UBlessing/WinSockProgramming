#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#define pass ;
#define pause system("PAUSE")

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	
	char *clientHostPtr;
	char clientHost[15];
	unsigned short clientPort;
	
	char msg[] = "¾È³çÇÏ¼¼¿ä";
	
	if(argc != 2) {
		printf("Usage: %s <port> \n", argv[0]);
		pause;
		exit(0);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 ) {
		perror("WSAStartup() Error");
		pause;
		exit(-1);
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(argv[1]));
	
	serverSock = socket(PF_INET, SOCK_STREAM, 0);
	if(serverSock == INVALID_SOCKET) {
		perror("socket() Error");
		pause;
		exit(-1);
	}
	
	if(bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		perror("bind() Error");
		pause;
		exit(-1);
	}
	
	if(listen(serverSock, 0) == SOCKET_ERROR) {
		perror("listen() Error");
		pause;
		exit(-1);
	}
	
	clientAddrSize = sizeof(clientAddr);
	while(1) {
		clientSock = accept(serverSock, (SOCKADDR*)&serverSock, &clientAddrSize);
		if(clientSock == INVALID_SOCKET) {
			continue;
		}
		
		clientHostPtr = inet_ntoa(clientAddr.sin_addr);
		strcpy_s(clientHost, sizeof(clientHost), clientHostPtr);
		clientPort = ntohs(clientAddr.sin_port);
		
		printf("%s:%d Connected!\n", clientHost, clientPort);
			
		send(clientSock, msg, sizeof(msg), 0);
		printf("Send to Complete : %s \n", msg);
		closesocket(clientSock);
	}
	
	closesocket(serverSock);
	WSACleanup();
	return 0;
}
