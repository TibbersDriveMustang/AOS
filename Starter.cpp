/*
 * Starter.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: kaushik sirineni
 */

#include "Starter.h"

Starter::Starter() {
	printf("In Starter\n");
	
	//decideAlgorithm();
}

Starter::~Starter() {
	for(int i = 0; i < NumNodes; ++i)
		delete Quorum[i];
	delete Quorum;
}

void Starter::init(){
	char controllerIP[15] = "10.176.67.108";
	int port = 3598;
	registerAtController(controllerIP, port);
}

void Starter::parseMsg(const string& s,const string& delim,std::vector<string>& tokens)
{
        size_t s0 = 0, s1 = string::npos;
        string token;
        while(s0 != string::npos)
          {

            s1 = s.find_first_of(delim, s0);

                // if(s1 != s0 && s1 != string::npos) // the second check added for space
				if(s1 != s0) // no need check Defect FIX  1,2 -> 2 will not be added in the list
            {
                  token = s.substr(s0, s1 - s0);

                if( token != "") 	
                {
                    //cout<<"Token :"<<token<<" length:"<<token.length()<<endl;
						//cout<<token<<endl;
					   tokens.push_back(token);
                }
            }
            s0 = s.find_first_not_of(delim, s1);
        }
        //EXIT
        token.clear();
        return;

    }

	


/*
 * send a message to controller when a node starts on a amachine.
 */
void Starter::registerAtController(char controllerIP[15],int port){
	//communication

	communication com;
	int sockfd = com.connectToServer(controllerIP,port);

	int z;
	char buf[128]={'\0',};
	z = gethostname(buf,sizeof buf);
	if ( z == -1 ) {
		fprintf(stderr, "%s: gethostname(2)\n",
		strerror(errno));
		exit(1);
	}
	int sd = 999;
	printf("\nContacted Controller, sent my hostname:%s\n",buf);
	com.writeToSocket(sockfd,buf,128);
	com.readFromSocket(sockfd,&id,sizeof(int));
	int qsize,nsize;
	com.readFromSocket(sockfd,&qsize,sizeof(int));
	com.readFromSocket(sockfd,&nsize,sizeof(int));
	//int size;
	//com.readFromSocket(sockfd,&size,sizeof(int));
	printf("Received ID: %d, Qsize: %d, NumNodes: %d\n",id,qsize,nsize);
	NumNodes = nsize;
	quorumSize = qsize;
	Quorum = new int*[nsize];
	for(int i = 0; i < nsize; ++i)
		Quorum[i] = new int[qsize];
	
	for (int i = 0; i < nsize; ++i) {
        for (int j = 0; j < qsize; ++j) {
            Quorum[i][j] = 0;
        }
    }
	for(int i=0;i<nsize;i++){
		for(int j=0;j<qsize;j++){
			printf("%d\t",Quorum[i][j]);
		}
		printf("\n");			
	}
	puts("Getting quorum table\n");
	char recvdMsg[4096] = {'\0',};
	com.readFromSocket(sockfd,recvdMsg,4095);
	string recvdStr = recvdMsg;
	vector<string> recvdValues;
	string delimiter = ":";
	parseMsg(recvdStr,delimiter,recvdValues);
	
	for (int i=0; i<recvdValues.size();i++)
	{
		cout<<recvdValues[i]<<endl; //<-- extract values from this vector and push into the attay in 123 line
		
	}
	for(int i=0; i<nsize;i++)
	{
		for(int j=0; j<qsize;j++)
		{
			//cout<<"Here"<<endl;
			Quorum[i][j] = atoi(recvdValues[i*qsize+j].c_str());
			//cout<<"Here1"<<endl;
		}
	}
	
	for(int i=0;i<nsize;i++){
		for(int j=0;j<qsize;j++){
	
			printf("%d\t",Quorum[i][j]);
		}
		printf("\n");	
		
	}
	/*for(int j = 0; j<nsize;j++){
		//printf("size: %d\n",sizeof(row)*sizeof(int));
		com.readFromSocket(sockfd,row,sizeof(row)*sizeof(int));
		for(int i =0;i<qsize;i++){
			Quorum[j][i] = row[i];
			printf("%d\t",Quorum[j][i]);
		}	
		printf("\n");
	}*/
	//delete row;
	int k = 0;//com.closeSocket(sockfd);
	if (k < 0) {
			printf("\nError in Closing");
			exit(0);
	}else
		printf("Node disconnected from Controller\n");

}

void Starter::decideAlgorithm(){
	printf("Enter the Algorithm for the nodes to follow:\n");
	printf("\t\t1:maekawa\t2:Torum\n");
	int algo=0;
	scanf("%d",&algo);
	if(algo == 1){
		Algorithm1();
	}else if(algo == 2){
		Algorithm2();

	}else
		printf("Invalid input\n");

}

void Starter::Algorithm1(){

}

void Starter::Algorithm2(){
	node = Torum::getInstance();
	node->init();
	node->setID(id);
	node->getQuorumTable(Quorum,quorumSize,NumNodes);

	wqueue<Packet*> queue;
	pthread_t thread1;
	pthread_create(&thread1, NULL, TorumProcess,(void *)&queue);

	pthread_t thread2;
	pthread_create(&thread2, NULL, TorumListen, (void *)&queue);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Torum execution done\n");
}

void *TorumListen(void* queue) {
	printf("Listener created");
	wqueue<Packet*> m_queue=*((wqueue<Packet*>*)queue);
	communication com;
	com.serverListen(1235,m_queue);
	return NULL;
}

void *TorumProcess(void* queue) {
	printf("Process created");
	wqueue<Packet*>*m_queue=(wqueue<Packet*>*)queue;

	// Remove 1 item at a time and process it. Blocks if no items are
	// available to process.
	for (int i = 0;; i++) {
		printf("thread , loop %d - waiting for item...\n", i);
		Packet* item = m_queue->remove();
		printf("thread  loop %d - got one item\n", i);
		printf("thread loop %d - item: messageType - %d, SEQ number - %ld\n",
				i, item->TYPE, item->SEQ);
		if (item->TYPE == 999) {
			//Recieve Quorum table and NodeID
		}

		delete item;
	}
	return NULL;
}
