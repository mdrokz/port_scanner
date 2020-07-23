// scanner.c : Defines the entry point for the application.


#include "scanner.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 2046

int main(void)
{
	struct port_data pdata;
	memset(&pdata, 0, sizeof(pdata));

	printf("Provide hostname or ip address,start port and end port:\n");

	fgets(&pdata.hostname, 200, stdin);
	fgets(&pdata.f_port, 6, stdin);
	fgets(&pdata.l_port, 6, stdin);

	pdata.hostname[strcspn(pdata.hostname, "\n")] = 0;
	pdata.f_port[strcspn(pdata.f_port, "\n")] = 0;
	pdata.l_port[strcspn(pdata.l_port, "\n")] = 0;

	pdata.fport = atoi(pdata.f_port);
	pdata.lport = atoi(pdata.l_port);

	port_scanner(pdata);

	return 0;
}

void port_scanner(struct port_data pdata)
{

	int i;
	int fport = pdata.fport;
	int lport = pdata.lport;
	int rc;
	int counter = 0;
	struct port_data localp = pdata;

	pthread_t threads[lport - fport];

	for (i = fport; i < lport; i++) {
		localp.c_port = i;
		rc = pthread_create(&threads[counter], NULL, scan_ports, (void *)&localp);
		if (rc) {
			printf("Error:unable to create thread, %d\n", rc);
			exit(-1);
		}
		counter++;
	}
	pthread_exit(NULL);
}

void* scan_ports(void* pdata) {

	struct port_data* p = (struct port_data*)pdata;

	struct addrinfo hints;
	struct addrinfo* result;
	struct hostent* host;

	int sockfd = 0;
	int status = 0;
	memset(&hints, 0, sizeof(hints));
	memset(&result, 0, sizeof(result));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	char* hostname = p->hostname;

	int cport = p->c_port;
	
	char port[6] = "";

	sprintf(port, "%d", cport);

	getaddrinfo(hostname, port, &hints, &result);

	sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (sockfd < 0)
	{
		printf("Port %d is NOT open.\n", cport);
		close(sockfd);
		freeaddrinfo(result);
	}
	else {

		status = connect(sockfd, result->ai_addr, result->ai_addrlen);
		if (status < 0)
		{
			printf("Port %d is NOT open.\n", cport);
			close(sockfd);
			freeaddrinfo(result);
		}
		else {
			printf("Port %d is open.\n", cport);
			close(sockfd);
			freeaddrinfo(result);
		}
	}

	pthread_exit(NULL);
}