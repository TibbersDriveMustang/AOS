#include "LexiQueue.h"


LexiQueue::LexiQueue(void)
{

}


LexiQueue::~LexiQueue(void)
{

}

AlgoMsg LexiQueue::remove(int origin, long seq){
	if(!pq.empty()){
			AlgoMsg top = pq.pop();
			return top;
		}
		return NULL;
}

AlgoMsg LexiQueue::top(){
	if(!pq.empty()){
		AlgoMsg top = pq.top();
		return top;
	}
	return NULL;
}

bool LexiQueue::add(AlgoMsg in){
	pq.push(in);
}

bool LexiQueue::update(){

}
