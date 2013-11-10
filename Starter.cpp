/*
 * Starter.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: kaushik sirineni
 */

#include "Starter.h"
#include "communication.h"
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
	Packet msg;
	msg.TYPE=0;
	communication com;
	strcpy(com.dest_IP_Address,"10.176.67.65");
	com.dest_port=1235;
	com.sendMessage(msg);
	
	//implement the reciever in reciever thread if msg type=0 listen to get the quorum table and nodeid
	
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
