#include <main.h>

#define MYPORT 3334
#define NTHREADS 10

//void *thread_function(void *);


int main(void) {
#if _WINDOWS_OS_
	SOCKET server_sockfd, client_sockfd;
	int server_len, client_len;
#else
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
#endif
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
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET(IPv4'ü kullanýn); SOCK_STREAM; 0(Varsayýlan protokolü kullanýn, TCP)
	if (server_sockfd == -1) {//SOCKET_ERROR
		printf("Socket Error\n");
		exit(1);
	}

	// struct sockaddr_in {
	//     short int               sin_family; /* AF_INT(IPv4'ü kullanýn) */
	//     unsigned short int sin_port;    /* Port */
	//     struct in_addr       sin_addr;   /* IP*/
	// };
	// sturct in_addr {
	//     unsigned long int s_addr;
	// };
	server_address.sin_family = AF_INET; // AF_INT(IPv4'ü kullanýn)
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); //	IP adresini ayarlayýn
	server_address.sin_port = 9734; //	Takma adý ayarla
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
		if (client_sockfd == -1) {//SOCKET_ERROR
			printf("Accept Error\n");
			exit(1);
		}

		for (i = 0; i < 250; i++) {
			recv(client_sockfd, &ch, 1, 0); // Linux socket programming read
			printf("char from client = %c\n", ch);
			ch++;
			send(client_sockfd, &ch, 1, 0); // Linux socket programming write
		}
		closesocket(client_sockfd); // Linux socket programming close
	}
}




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
//	Sleep(3000);
//	/*....other codes....*/
//
//
//
//	return 0;
//
//}