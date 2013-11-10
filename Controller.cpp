#include "Controller.h"
#define MAXNODES 16

//Msg type=100
Controller::Controller(void):QuorumTable{{0, 1, 2, 3, 4, 8, 12}, 
		{0, 1, 2, 3, 5, 9, 13},
		{0, 1, 2, 3, 6, 10, 14},
		{0, 1, 2, 3, 7, 11, 15},
		{4, 5, 6, 7, 0, 8, 12},
		{4, 5, 6, 7, 1, 9, 13},
		{4, 5, 6, 7, 2, 10, 14},
		{4, 5, 6, 7, 3, 11, 15},
		{8, 9, 10, 11, 0, 4, 12},
		{8, 9, 10, 11, 1, 5, 13},
		{8, 9, 10, 11, 2, 6, 14},
		{8, 9, 10, 11, 3, 7, 15},
		{12, 13, 14, 15, 0, 4, 8},
		{12, 13, 14, 15, 1, 5, 9},
		{12, 13, 14, 15, 2, 6, 10},
		{12, 13, 14, 15, 3, 7, 11}
}
{

}
Controller::~Controller(void)
{
	delete QuorumTable;
}

void DieWithError1(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

void DieWithError1(char *errorMessage);  /* Error handling function */

void Controller::handle(int clntSock1,char* client_ip,int counter)
{
	/*QuorumTable[16][7]={{0, 1, 2, 3, 4, 8, 12}, 
											{0, 1, 2, 3, 5, 9, 13},
											{0, 1, 2, 3, 6, 10, 14},
											{0, 1, 2, 3, 7, 11, 15},
											{4, 5, 6, 7, 0, 8, 12},
											{4, 5, 6, 7, 1, 9, 13},
											{4, 5, 6, 7, 2, 10, 14},
											{4, 5, 6, 7, 3, 11, 15},
											{8, 9, 10, 11, 0, 4, 12},
											{8, 9, 10, 11, 1, 5, 13},
											{8, 9, 10, 11, 2, 6, 14},
											{8, 9, 10, 11, 3, 7, 15},
											{12, 13, 14, 15, 0, 4, 8},
											{12, 13, 14, 15, 1, 5, 9},
											{12, 13, 14, 15, 2, 6, 10},
											{12, 13, 14, 15, 3, 7, 11}
	};*/
	
	communication com;
	char msg[32];
	com.readFromSocket(clntSock1,msg,32*sizeof(char));
	printf("Client %s is UP",msg);
	int32_t qColSize=7;
	int32_t qRowSize=16;
	com.writeToSocket(clntSock1,&counter,sizeof(int));
	com.writeToSocket(clntSock1,&qColSize,sizeof(qColSize)*sizeof(int32_t));
	com.writeToSocket(clntSock1,&qRowSize,sizeof(qColSize)*sizeof(int32_t));
	com.writeToSocket(clntSock1,QuorumTable,sizeof(QuorumTable));
	close(clntSock1);
}

void *listener(void*) {
	Controller con;
	
	printf("Listener created");
	/*communication com;
	com.serverListen(1235,m_queue);*/
	int counter=1;
	 int servSock;                    /* Socket descriptor for server */
	    int clntSock;                    /* Socket descriptor for client */
	    struct sockaddr_in echoServAddr; /* Local address */
	    struct sockaddr_in echoClntAddr; /* Client address */
	    unsigned short echoServPort;     /* Server port */
	    socklen_t clntLen;            /* Length of client address data structure */

	   
	    echoServPort = 3498;  /* First arg:  local port */

	    /* Create socket for incoming connections */
	    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	        DieWithError1("socket() failed");

	    /* Construct local address structure */
	    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
	    echoServAddr.sin_family = AF_INET;                /* Internet address family */
	    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

	    /* Bind to the local address */
	    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	        DieWithError1("bind() failed");

	    /* Mark the socket so it will listen for incoming connections */
	    if (listen(servSock, MAXPENDING) < 0)
	        DieWithError1("listen() failed");
	    //int del=0;
	    for (;counter<MAXNODES+1;) /* Run forever */
	    {
	        /* Set the size of the in-out parameter */
	        clntLen = sizeof(echoClntAddr);

	        /* Wait for a client to connect */
	        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
	            DieWithError1("accept() failed");

	        /* clntSock is connected to a client! */
	        char *client_ip = inet_ntoa(echoClntAddr.sin_addr);
	        printf("\nClient socket %d, addlen : %d %s\n",clntSock,sizeof(client_ip),client_ip);
	        con.handle(clntSock,client_ip,counter);
	        counter++;
	        
	    }
	
	
	
	return NULL;
}

int main()
{
	
	
	printf("Welcome to Controller Function!!");
	pthread_t listen;
		pthread_create(&listen, NULL,listener, NULL);
		pthread_join(listen,NULL);
		return 0;
}
