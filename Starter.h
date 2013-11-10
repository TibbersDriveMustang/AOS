/*
 * Starter.h
 *
 *  Created on: Nov 6, 2013
 *      Author: kaushik sirineni
 */

#ifndef STARTER_H_
#define STARTER_H_

#include <iostream>
#include <pthread.h>
#include "Algo9.h"

using namespace std;

class Starter {
private:
	Torum *node;
public:
	Starter();
	virtual ~Starter();
	void registerAtController(char controllerIP[],int port);
	void startListener(Torum *node);
};

#endif /* STARTER_H_ */
