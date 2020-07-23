// test.c : Defines the entry point for the application.
//

#include "scanner.h"
//#include <iostream>
//#include "stdlib.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>

#define MAX_SIZE 2046

int main(void)
{
	// 192.168.100.24
	char tIP[200] = "";
	char f_port[6] = "";
	char l_port[6] = "";
	//char tIP[16] = "172.19.255.54";
	printf("Provide hostname or ip address,start port and end port:\n");

	fgets(&tIP, 200, stdin);
	fgets(&f_port, 6, stdin);
	fgets(&l_port, 6, stdin);

	tIP[strcspn(tIP, "\n")] = 0;
	f_port[strcspn(f_port, "\n")] = 0;
	l_port[strcspn(l_port, "\n")] = 0;

	port_scanner(tIP, f_port, l_port);

	return 0;
}

void port_scanner(char ip_address[200], char f_port[6], char l_port[6])
{
	struct addrinfo hints;
	struct addrinfo* result;
	struct hostent* host;
	int sockfd = 0;
	int i;
	int status = 0;
	memset(&hints, 0, sizeof(hints));
	memset(&result, 0, sizeof(result));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int fport = atoi(f_port);
	int lport = atoi(l_port);

	for (i = fport; i < lport; i++) {
		char port[6] = "";

		sprintf(port, "%d", i);

		getaddrinfo(ip_address, port, &hints, &result);

		sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (sockfd < 0)
		{
			printf("Port %s is NOT open.\n", i);
			close(sockfd);
			freeaddrinfo(result);
		}
		else {

			status = connect(sockfd, result->ai_addr, result->ai_addrlen);
			if (status < 0)
			{
				printf("Port %d is NOT open.\n", i);
				close(sockfd);
				freeaddrinfo(result);
			}
			else {
				printf("Port %d is open.\n", i);
				close(sockfd);
				freeaddrinfo(result);
			}
		}
	}

	freeaddrinfo(result);

	return;
}
