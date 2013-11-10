
#include"communication.h"


/*struct AlgoMsg{
	int TYPE; // 0: request_token, 1: have-token, 2: release, 3:send-token
	int ORIGIN;
	long SEQ;
	int sender;
}__attribute__((packed));*/





/*int main(int argc, char *argv[])
{
	AlgoMsg message;
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
}*/


int communication::sendMessage(struct Packet message) {
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








void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}


void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket, void* queue)
{
	wqueue<Packet*>*m_queue = (wqueue<Packet*>*)queue;
	
    char echoBuffer[RCVBUFSIZE] = {'\0'};        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    Packet message;
    printf("Entered handling client");
    
    /* Receive message from client */
   /* if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");*/
    if ((recvMsgSize = recv(clntSocket, &message, sizeof(message), 0)) < 0)
           DieWithError("recv() failed");
printf("Message type %d",message.TYPE);
printf("Message Originator %d", message.ORIGIN);
printf("Message Sequ %ld", message.SEQ);
printf("Message sender %ld", message.sender);
Packet *message1;
	message1 = (struct Packet *)malloc(sizeof(struct Packet));
	message1->TYPE=message.TYPE;
	message1->ORIGIN=message.ORIGIN;
	message1->SEQ=message.SEQ;
	message1->sender=message.sender;
	m_queue->add(message1);
    /* Send received string and receive again until end of transmission */
    
  /*  while (recvMsgSize > 0)       zero indicates end of transmission 
    {
         Echo message back to client 
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");

         See if there is more data to receive 
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            	DieWithError("recv() failed");

             Terminate the string! 
        	printf("%s\n", echoBuffer);


    }*/

    close(clntSocket);    /* Close client socket */
}
int communication::serverListen(int portNum,void* queue)
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    int clntLen;            /* Length of client address data structure */

   
    echoServPort = portNum;  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    int del=0;
    for (;del<1;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
            DieWithError("accept() failed");

        /* clntSock is connected to a client! */

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        HandleTCPClient(clntSock,(void *)&queue);
        del++;
    }
    /* NOT REACHED */
}




