#include<stdio.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include "wqueue.h"
#include "communication.h"

void *function(void* queue) {
	printf("Listener createxdd");
	wqueue<Packet*> m_queue=*((wqueue<Packet*>*)queue);
	communication com;
	com.serverListen(1235,m_queue);
	return NULL;
}

void *fun(void* queue) {
	printf("Procdess hrw cr");
	wqueue<Packet*>*m_queue=(wqueue<Packet*>*)queue;

	// Remove 1 item at a time and process it. Blocks if no items are 
	// available to process.
	for (int i = 0;; i++) {
		printf("thread , loop %d - waiting for item...\n", i);
		Packet* item = m_queue->remove();
		printf("thread  loop %d - got one item\n", i);
		printf("thread loop %d - item: messageType - %d, SEQ number - %ld\n",
				i, item->TYPE, item->SEQ);
		if (item->TYPE == 999) {
			//Recieve Quorum table and NodeID
		}

		delete item;
	}
	return NULL;
}
int main() {

	wqueue<Packet*> queue;

	pthread_t thread1;
	pthread_create(&thread1, NULL, fun,(void *)&queue);

	pthread_t thread2;
	pthread_create(&thread2, NULL, function, (void *)&queue);

	 	communication com;
		com.serverListen(1234,queue);
		
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("done\n");
	exit(0);

	/*	 	strcpy(c.dest_IP_Address,"10.176.67.65");
	 printf(c.dest_IP_Address);
	 c.dest_port=1235;
	 
	 c.sendMessage(message);*/
	return 0;
}
