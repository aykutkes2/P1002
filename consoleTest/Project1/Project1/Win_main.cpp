#define _MAC_OS_		( __APPLE__ | __MACH__ )
#if (!_MAC_OS_)
#define _LINUX_OS_		( __linux__ | linux | __linux )
#if (!_LINUX_OS_)
#define _WINDOWS_OS_	( _WIN32 | _WIN64 )	
#endif
#endif

#if _LINUX_OS_
#include <stdio.h> 
#include <stdlib.h> 
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

#define MYPORT 3334


//
//int main(void)
//
//{
//#if _WINDOWS_OS_
//	SOCKET sockfd;
//#else
//	int sockfd; /* socket file descriptor */
//#endif
//
//	struct sockaddr_in my_addr;
//
//
//#if _WINDOWS_OS_
//	WSADATA wsadata;
//	if (WSAStartup(0x101, (LPWSADATA)&wsadata) != 0) {
//		printf("Winsock Error\n");
//		exit(1);
//	}
//#endif
//	sockfd = socket(AF_INET, SOCK_STREAM, 0);
//
//	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//
//	{
//
//		perror("Server-socket() error lol!");
//
//		return 0;
//
//	}
//
//	else
//
//		printf("Server-socket() sockfd is OK...\n");
//
//
//
//	/* host byte order */
//
//	my_addr.sin_family = AF_INET;
//
//	/* short, network byte order */
//
//	my_addr.sin_port = htons(MYPORT);
//
//	my_addr.sin_addr.s_addr = INADDR_ANY;
//
//	/* zero the rest of the struct */
//
//	memset(&(my_addr.sin_zero), 0, 8);
//
//
//
//	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
//
//	{
//
//		perror("Server-bind() error lol!");
//
//		return 0;
//
//	}
//
//	else
//
//		printf("Server-bind() is OK...\n");
//
//
//
//	/*....other codes....*/
//
//
//
//	return 0;
//
//}


















int main(void) {
#if _WINDOWS_OS_
	SOCKET server_sockfd, client_sockfd;
#else
	int server_sockfd, client_sockfd;
#endif
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

#if _WINDOWS_OS_
	// Winsock DLL
	WSADATA wsadata;
	if (WSAStartup(0x101, (LPWSADATA)&wsadata) != 0) {
		printf("Winsock Error\n");
		exit(1);
	}
#endif
	// server socket
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET(使用IPv4); SOCK_STREAM; 0(使用預設通訊協定，即TCP)
	if (server_sockfd == SOCKET_ERROR) {
		printf("Socket Error\n");
		exit(1);
	}

	// struct sockaddr_in {
	//     short int               sin_family; /* AF_INT(使用IPv4) */
	//     unsigned short int sin_port;    /* Port(埠號) */
	//     struct in_addr       sin_addr;   /* IP位址 */
	// };
	// sturct in_addr {
	//     unsigned long int s_addr;
	// };
	server_address.sin_family = AF_INET; // AF_INT(IPv4'ü kullanın)
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); //	IP adresini ayarlayın
	server_address.sin_port = 9734; //	Takma adı ayarla
	server_len = sizeof(server_address);

	if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
		printf("Bind Error\n");
		exit(1);
	}

	if (listen(server_sockfd, 5) < 0) {
		printf("Listen Error\n");
		exit(1);
	}

	while (1) {
		char i, ch;
		printf("Server waiting...\n");
		client_len = sizeof(client_address);

		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		if (client_sockfd == SOCKET_ERROR) {
			printf("Accept Error\n");
			exit(1);
		}

		for (i = 0; i < 250; i++) {
			recv(client_sockfd, &ch, 1, 0); // Linux socket programming 為 read
			printf("char from client = %c\n", ch);
			ch++;
			send(client_sockfd, &ch, 1, 0); // Linux socket programming 為 write
		}
		closesocket(client_sockfd); // Linux socket programming 為 close
	}
}


