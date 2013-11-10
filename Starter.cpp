/*
 * Starter.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: kaushik sirineni
 */

#include "Starter.h"
#include "communication.h"
Starter::Starter() {
	char controllerIP[] = "10.176.67.108";
	int port = 3498;
	registerAtController(controllerIP, port);
	decideAlgorithm();
}

Starter::~Starter() {

}

/*
 * send a message to controller when a node starts on a amachine.
 */
void Starter::registerAtController(char controllerIP[],int port){
	//communication

	communication com;
	int sockfd = com.connectToServer(controllerIP,port);

	int z;
	char buf[32];
	z = gethostname(buf,sizeof buf);
	if ( z == -1 ) {
		fprintf(stderr, "%s: gethostname(2)\n",
		strerror(errno));
		exit(1);
	}
	com.writeToSocket(sockfd,(void*)buf,sizeof(buf)*sizeof(char));
	com.readFromSocket(sockfd,&id,sizeof(id)*sizeof(int));
	int32_t qsize,nsize;
	com.readFromSocket(sockfd,&qsize,sizeof(qsize)*sizeof(int32_t));
	com.readFromSocket(sockfd,&nsize,sizeof(nsize)*sizeof(int32_t));
	int32_t quorum[nsize][qsize];
	com.readFromSocket(sockfd,quorum,qsize*nsize*sizeof(int32_t));
	Quorum = new int*[qsize];
		for(int i = 0; i < nsize; ++i)
			Quorum[i] = new int[qsize];
	for(int j = 0; j<nsize;j++){
	for(int i =0;i<qsize;i++){
		Quorum[j][i] = quorum[j][i];
		printf("%d\t",quorum[j][i]);
	}
	printf("\n");
	}
	com.closeSocket(sockfd);

}

void Starter::decideAlgorithm(){
	printf("Enter the Algorithm for the nodes to follow:\n");
	printf("\t\t1:maekawa\t2:Torum\n");
	int algo=0;
	scanf("%d",&algo);
	if(algo == 0){
		//maekawa
	}else if(algo == 1){
		//Torum

	}else
		printf("Invalid input\n");

}

void Starter::Algorithm2(){
	node = Torum::getInstance();
			node->init();
			node->setID(id);
			node->getQuorumTable(Quorum,quorumSize,NumNodes);
}
void Starter::Algorithm1(){

}
