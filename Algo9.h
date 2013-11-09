#ifndef ALGO9_H_
#define ALGO9_H_

#pragma once
#include <iostream>
#include <vector>
#include "MessageFormat.h"
#include "LexiQueue.h"
#include <pthread.h>

 using namespace std;
class Torum
{
protected:
	int ID;
	long sequenceNo;
	int HOLDER;
	int **quorum;
	int quorumsize;
	int NumNodes;
	//vector<vector<int>> quorum;;
	pthread_mutex_t sharedQLock;
	LexiQueue *queue;


public:
	static Torum* getInstance();
	void init();
	bool setID(int id);
	bool getQuorumTable(int **quorumtable,int qsize,int nnodes);
	bool requestCS();
	bool receiveRequest(AlgoMsg request);
	bool receiveToken(AlgoMsg request);
	bool receiveRelease(AlgoMsg request);
	bool receiveHaveTkn(AlgoMsg request);
	bool sendToken();

private:
	Torum(){};
	Torum(Torum const& copy){};
	Torum& operator=(Torum const& copy){};
	static Torum* instance;
};

#endif;
