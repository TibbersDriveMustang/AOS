#ifndef ALGO9_H_
#define ALGO9_H_

#include <iostream>
#include <vector>
#include "MessageFormat.h"
#include "LexiQueue.h"
#include <pthread.h>
#include <stdio.h>

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
	bool receiveRequest(Packet request);
	bool receiveToken(Packet request);
	bool receiveRelease(Packet request);
	bool receiveHaveTkn(Packet request);
	bool sendToken();

private:
	Torum(){};
	Torum(Torum const& copy){};
	Torum& operator=(Torum const& copy){};
	static Torum* instance;
};

#endif;
