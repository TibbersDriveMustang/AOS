#include "Algo9.h"

Torum* Torum::instance = NULL;

void Torum::init()
{
	sequenceNo = 0;
	HOLDER = -1;
	queue = new LexiQueue();
	pthread_mutex_init(&sharedQLock,NULL);
}

Torum* Torum::getInstance()
        {
            if(!instance){
            	instance = new Torum();
            }
            return instance;
        }

bool Torum::setID(int id){
	ID = id;
	return true;
}
bool Torum::getQuorumTable(int **quorumtable,int qsize,int Nnodes){
	quorum = quorumtable;
	quorumsize = qsize;
	NumNodes = Nnodes;
	return true;
}

bool Torum::requestCS(){
	sequenceNo++;

	struct Packet request;
	request.TYPE = REQUEST;
	request.ORIGIN = ID;
	request.sender = ID;
	request.SEQ = sequenceNo;

	pthread_mutex_lock(&sharedQLock);
	queue->add(request);
	pthread_mutex_unlock(&sharedQLock);

	if( HOLDER== -1 ){
		for(int i=0;i<quorumsize;i++){
			//send(request,quorum[ID][i]);
		}
	}else{
		//send(request,HOLDER);
	}
	return true;
}

bool Torum::receiveRequest(Packet request){
	if(sequenceNo<request.SEQ) sequenceNo = request.SEQ;
	//check if the token is with this node
	if(HOLDER==ID){
		queue->add(request);
	}else{// token is not with this node
		//request from its master
		if(request.ORIGIN == request.sender){
			queue->add(request);
		}

	}
	return true;
}

bool Torum::receiveToken(Packet token){
	if(sequenceNo<token.SEQ) sequenceNo = token.SEQ;
	Packet top = queue->top();
	if(ID == top.ORIGIN ){// if current node is top of the queue
		//HOLDER = ID;
		struct Packet havetkn;
		havetkn.TYPE = HAVE_TOKEN;
		havetkn.ORIGIN = ID;
		havetkn.sender = ID;
		havetkn.SEQ = sequenceNo;
		for(int i=0;i<quorumsize;i++){
			//send(havetkn,quorum[ID][i]);
		}
	}else{
		//send(token,top.sender);
	}
	return true;
}

bool Torum::receiveRelease(Packet release){
	if(sequenceNo<release.SEQ) sequenceNo = release.SEQ;
	HOLDER = -1;
	queue->update();
	return true;
}

bool Torum::receiveHaveTkn(Packet havtkn){
	if(sequenceNo<havtkn.SEQ) sequenceNo = havtkn.SEQ;
	HOLDER = havtkn.ORIGIN;
	queue->remove(havtkn.ORIGIN,havtkn.SEQ);
	Packet top = queue->top();
	//send(top,HOLDER);
	return true;
}

bool Torum::sendToken(){
	Packet top = queue->top();

	struct Packet release;
		release.TYPE = RELEASE;
		release.ORIGIN = ID;
		release.sender = ID;
		release.SEQ = sequenceNo;
	for(int i=0;i<quorumsize;i++){
			//send(release,quorum[ID][i]);
		i++;
		}
	queue->update();
	
	struct Packet token;
		token.TYPE = SEND_TOKEN;
		token.ORIGIN = ID;
		token.sender = ID;
		token.SEQ = sequenceNo;
		//send(token,top.sender);
		return true;
}
