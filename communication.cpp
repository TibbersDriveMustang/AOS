#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include<stdlib.h>
#include<string>
#include<errno.h>
#include <errno.h>
#include<string.h>
using namespace std;

struct mtype{
	int TYPE; // 0: request_token, 1: have-token, 2: release, 3:send-token
	int ORIGIN;
	long SEQ;
	int sender;
}__attribute__((packed));



class communication {
public:
	char dest_IP_Address[13];
	string source_IP_Address;
	int dest_port;

	int sendMessage(struct mtype message);

};

int main(int argc, char *argv[])
{
	mtype message;
	message.TYPE=1;
	message.ORIGIN=2;
	message.SEQ=12121;
	message.sender=4;
	communication c;
	
	
	strcpy(c.dest_IP_Address,"10.176.67.65");
	printf(c.dest_IP_Address);
	c.dest_port=1235;
	c.sendMessage(message);
	return 0;
}


int communication::sendMessage(struct mtype message) {
	int sockfd;
	struct sockaddr_in servaddr;
  
	/* creating a socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error in socket");
		exit(0);
	}
    printf("Socket created");
	/* configuring server address structure */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(this->dest_port);
	 printf("Socket configured");
/*	servaddr.sin_addr.s_addr = inet_addr(this->dest_IP_Address);*/
	if (inet_pton(AF_INET, this->dest_IP_Address, &servaddr.sin_addr) <= 0) {
		printf("\n Error in inet_pton");
		exit(0);
	}

	/* connecting to the server */
	
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		printf("\nError in connect");
		exit(0);
	}
	 printf("Socket connected to server");
	/*Sending to the server*/
	printf("%d sizeof  ",sizeof(message));
	ssize_t n_send = send(sockfd, (void *) &message, sizeof(message), 0);
	if (n_send < 0) {
		printf("\nError in Sending");
		exit(0);

	}
	 printf("message sent");
return 0;
}




