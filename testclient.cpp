#include<stdio.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include "wqueue.h"
#include "communication.h"

void *function(void* queue)
{
	communication com;
	com.serverListen(1235,(void *)&queue));
	return NULL;
}

void *fun(void* queue)
{
	wqueue<Packet*>*m_queue=(wqueue<Packet*>*)queue;

	// Remove 1 item at a time and process it. Blocks if no items are 
			// available to process.
			for (int i = 0;; i++) {
				printf("thread , loop %d - waiting for item...\n",i);
				Packet* item = m_queue->remove();
				printf("thread  loop %d - got one item\n", i);
				printf("thread loop %d - item: messageType - %d, SEQ number - %ld\n", i, item->TYPE, item->SEQ);
				if(item->TYPE == 999)
				{
					//Recieve Quorum table and NodeID
				}
				
				
				delete item;
			}
			return NULL;
}
int main() {

	Packet *message1;
	message1 = (struct Packet *)malloc(sizeof(struct Packet));
	message1->TYPE=1;
	message1->ORIGIN=2;
	message1->SEQ=12121;
	message1->sender=4;

	Packet *message2;
	message2 = (struct Packet *)malloc(sizeof(struct Packet));
	message2->TYPE=2;
	message2->ORIGIN=3;
	message2->SEQ=3232;
	message2->sender=5;
	communication c;

	wqueue<Packet*> queue;

	queue.add(message1);
	queue.add(message2);
	/*ConsumerThread* thread1 = new ConsumerThread(queue);
	thread1->start();*/
	pthread_t thread1;
	pthread_create(&thread1, NULL, fun,(void *)&queue);
	
	Packet *message3;
	message3 = (struct Packet *)malloc(sizeof(struct Packet));
	message3->TYPE=3;
	message3->ORIGIN=3;
	message3->SEQ=34332;
	message3->sender=5;
	queue.add(message3);
	while (queue.size() < 0)
		;
	pthread_join(thread1,NULL);
	
	pthread_t thread2;
		
		/* thread1 = (pthread_t*)malloc(sizeof(pthread_t));*/
		 pthread_create(&thread2, NULL, function, (void *)&queue);
		 pthread_join(thread2,NULL);
		 
		 
	printf("done\n");
	exit(0);

	/*	 	strcpy(c.dest_IP_Address,"10.176.67.65");
	 printf(c.dest_IP_Address);
	 c.dest_port=1235;
	 
	 c.sendMessage(message);*/
	return 0;
}
