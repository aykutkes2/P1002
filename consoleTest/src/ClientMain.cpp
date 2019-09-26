#include <main.h>

#define MYPORT 3334
#define NTHREADS 10

//void *thread_function(void *);

int main(void) {
#if _WINDOWS_OS_
	SOCKET sockfd;
	int len;
#else
	int sockfd;
	socklen_t len;
#endif
	struct sockaddr_in address;
	int result;
	char i, ch = 'A';

#if _WINDOWS_OS_
	WSADATA wsadata;
	if (WSAStartup(0x101, (LPWSADATA)&wsadata) != 0) {
		printf("Winsock Error\n");
		exit(1);
	}
#endif
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


