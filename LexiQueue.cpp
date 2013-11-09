#include "LexiQueue.h"


LexiQueue::LexiQueue(void)
{

}


LexiQueue::~LexiQueue(void)
{

}

AlgoMsg LexiQueue::remove(int origin, long seq){
	AlgoMsg top;
	top.TYPE = -1;
	if(!pq.empty()){
			top = (AlgoMsg)pq.top();
			pq.pop();
			return top;
		}
		return top;
}

AlgoMsg LexiQueue::top(){
	AlgoMsg top;
	top.TYPE = -1;
	if(!pq.empty()){
		top = pq.top();
		return top;
	}
	return top;
}

bool LexiQueue::add(AlgoMsg in){
	pq.push(in);
	return true;
}

bool LexiQueue::update(int **quorum,int qsize,int ID){
	priority_queue<AlgoMsg, vector<AlgoMsg>, CompareMessages> tempq;

	while(!pq.empty()){
		AlgoMsg top = pq.top();
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

