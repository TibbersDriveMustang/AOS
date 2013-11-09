/*
 * Starter.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: kaushik sirineni
 */

#include "Starter.h"

Starter::Starter() {
	node = Torum::getInstance();
	node->init();
	registerAtController();
	startListener(node);
}

Starter::~Starter() {

}

/*
 * send a message to controller when a node starts on a amachine.
 */
void Starter::registerAtController(){
	//communication
	//send a status message
	int id;//receive a node id
	node->setID(id);
	//receive quorum table
	int **quorum;
	node->getQuorumTable(quorum,5,16);

}

void Starter::startListener(Torum *node){
	//create new thread and pass this node reference to it
	// thread will listen for incoming connections.
	// if a message is received we handle it by calling appropriate method.
}
