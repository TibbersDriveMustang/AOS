#include "Controller.h"
#include <iostream>
using namespace std;

#define MAXNODES 16
#define MAXLENGTH 15
static char mapIPtoID[MAXNODES][MAXLENGTH];


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
	//delete QuorumTable;
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
	char msg[128]={'\0',};
	int sd=0;
	com.readFromSocket(clntSock1,msg,128);
	puts("returned\n");
	printf("Client %s is UP",msg);
	puts("\n");
	int qColSize=7;
	int qRowSize=16;
	puts("\n");
	com.writeToSocket(clntSock1,&counter,sizeof(int));
	com.writeToSocket(clntSock1,&qColSize,sizeof(int));
	com.writeToSocket(clntSock1,&qRowSize,sizeof(int));
	//int size = sizeof(QuorumTable);
	//com.writeToSocket(clntSock1,&size,sizeof(int));
	puts("quorum table");
	for(int i=0;i<qRowSize;i++){
		for(int j=0;j<qColSize;j++){
			printf("%d\t",QuorumTable[i][j]);
		}
		printf("\n");	
		
	}
	int row[qColSize];// = new int[qColSize];
	//for(int i=0;i<qColSize;i++)
	//row[i] = QuorumTable[14][i];
	//com.writeToSocket(clntSock1,row,sizeof(row)*sizeof(int));
	string strToSend,tempStr; strToSend.clear(); tempStr.clear();
	char temp[5] = {0,};
	for(int i=0;i<qRowSize;i++){
		for(int j=0;j<qColSize;j++){
			//row[j] = QuorumTable[i][j];
			snprintf(temp,4,"%d",QuorumTable[i][j]);
			tempStr = temp;
			strToSend += tempStr;
			strToSend += ":";
			memset(&temp,0,sizeof(temp));
			tempStr.clear();
		}
		//printf("size: %d\n",sizeof(row)*sizeof(int));
		//com.writeToSocket(clntSock1,row,sizeof(row)*sizeof(int));	
		
	}
	com.writeToSocket(clntSock1,const_cast<char*> (strToSend.c_str()), strToSend.length());	
	cout<<"Sent Msg - "<<strToSend<<endl;
	
	printf("Counter value %d",counter);
	strcpy(mapIPtoID[counter], client_ip);
	printf("MaptoIP %s",mapIPtoID[counter]);
		
	//delete row;
	int k = close(clntSock1);
	if (k < 0) {
		printf("\nError in Closing");
		exit(0);
	}

}

void *listener(void*) {
	
	Controller con;
	printf("In Listener\n");
	/*communication com;
	com.serverListen(1235,m_queue);*/
	int counter=1;
	 int servSock;                    /* Socket descriptor for server */
	    int clntSock;                    /* Socket descriptor for client */
	    struct sockaddr_in echoServAddr; /* Local address */
	    struct sockaddr_in echoClntAddr; /* Client address */
	    unsigned short echoServPort;     /* Server port */
	    socklen_t clntLen;            /* Length of client address data structure */

	   
	    echoServPort = LISTEN_PORT;  /* First arg:  local port */

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
	    for (;counter<2+1;) /* Run forever */
	    {
	        /* Set the size of the in-out parameter */
	        clntLen = sizeof(echoClntAddr);

	        /* Wait for a client to connect */
	        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
	        {
	        	close(servSock);
	        	DieWithError1("accept() failed");
	        }

	        /* clntSock is connected to a client! */
	        char *client_ip = inet_ntoa(echoClntAddr.sin_addr);
	        printf("\nClient socket %d, addlen : %d %s\n",clntSock,sizeof(client_ip),client_ip);
	        con.handle(clntSock,client_ip,counter);
	        counter++;
	        printf("Counter value %d",counter);
	    }
	
	
	printf("Came out of for");
	//return NULL;
}

void sendTokenToNode()
{
	printf("In send token");
	//Send token
	Packet pack;
	pack.TYPE=SEND_TOKEN;
	pack.ORIGIN=45;
	pack.SEQ=1;
	pack.sender=45;
	
	communication com;
	printf("Map to ID %s",mapIPtoID[0]);
	char desIP[15];
	strncpy(desIP,mapIPtoID[1],15);
	printf("des to ID %s",desIP);
	
	com.sendMessage(pack,desIP,LISTEN_PORT);
}
int main()
{
/*	int i;
	for(i=0; i <MAXNODES ; i++) {
		mapIPtoID[i] = (char *)malloc(sizeof(char)*MAXLENGTH);
	}
	*/
	printf("Welcome to Controller Function!!\n");
	pthread_t listen;
		pthread_create(&listen, NULL,listener, NULL);
		pthread_join(listen,NULL);
		
		//Enter the algo and send token to 1 if algo=2
		
		printf("Enter the Algorithm for the nodes to follow:\n");
		printf("\t\t1:Maekawa\t2:Torum\n");
		int algo=0;
		scanf("%d",&algo);
		if(algo == 2){
			sendTokenToNode();

		}else
			printf("Invalid input\n");
		
		
		return 0;
}
