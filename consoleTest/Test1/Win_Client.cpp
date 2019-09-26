
#define _WINDOWS_OS_	( _WIN32 | _WIN64 )	
#define _LINUX_OS_		( __linux__ | linux | __linux )
#define _MAC_OS_		( __APPLE__ | __MACH__ )

#if _LINUX_OS_
#include <cstdio>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#else
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

int main() {
	SOCKET sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char i, ch = 'A';

	WSADATA wsadata;
	if (WSAStartup(0x101, (LPWSADATA)&wsadata) != 0) {
		printf("Winsock Error\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 9734;
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if (result == -1) {
		printf("Connetc Error");
		exit(1);
	}
	for (i = 0; i < 250; i++) {
		send(sockfd, &ch, 1, 0);
		recv(sockfd, &ch, 1, 0);
		printf("char from server = %c\n", ch);
	}
	closesocket(sockfd);
	exit(0);
}


