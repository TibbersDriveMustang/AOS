#include "LexiQueue.h"


LexiQueue::LexiQueue(void)
{

}


LexiQueue::~LexiQueue(void)
{

}

Packet LexiQueue::remove(int origin, long seq){
	Packet top;
	top.TYPE = -1;
	if(!pq.empty()){
			top = (Packet)pq.top();
			pq.pop();
			return top;
		}
		return top;
}

Packet LexiQueue::top(){
	Packet top;
	top.TYPE = -1;
	if(!pq.empty()){
		top = pq.top();
		return top;
	}
	return top;
}

bool LexiQueue::add(Packet in){
	pq.push(in);
	return true;
}

bool LexiQueue::update(int **quorum,int qsize,int ID){
	priority_queue<Packet, vector<Packet>, CompareMessages> tempq;

	while(!pq.empty()){
		Packet top = pq.top();
		pq.pop();
		for(int j=0;j<qsize;j++){
			if(quorum[top.ORIGIN][j] == ID){
				tempq.push(top);
				break;
			}
		}

	}
	pq = tempq;
	return true;
}

