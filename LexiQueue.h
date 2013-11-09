#ifndef LEXIQUEUE_H_
#define LEXIQUEUE_H_

#pragma once
#include"MessageFormat.h"
#include<cstdlib>
#include <queue>

using namespace std;

class CompareMessages{
public:
	bool operator()(AlgoMsg& m1,AlgoMsg& m2){
		if(m2.SEQ < m1.SEQ) return true;
		if(m2.SEQ == m1.SEQ && m2.ORIGIN < m1.ORIGIN) return true;
		return false;
	}
};
class LexiQueue
{
protected:
	priority_queue<AlgoMsg, vector<AlgoMsg>, CompareMessages> pq;
public:
	LexiQueue(void);
	~LexiQueue(void);
	AlgoMsg top();
	AlgoMsg remove(int origin, long seq);
	bool add(AlgoMsg in);
	bool update();
};

#endif
