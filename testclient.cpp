#include<stdio.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>


#include "wqueue.h"
#include "communication.h"

/*class ConsumerThread : public Thread {
	wqueue<AlgoMsg*>& m_queue;

public:
	ConsumerThread(wqueue<AlgoMsg*>& queue) :
		m_queue(queue) {
	}

	void* run() {
		// Remove 1 item at a time and process it. Blocks if no items are 
		// available to process.
		for (int i = 0;; i++) {
			printf("thread %lu, loop %d - waiting for item...\n",
					(long unsigned int)self(), i);
			AlgoMsg* item = m_queue.remove();
			printf("thread %lu, loop %d - got one item\n",
					(long unsigned int)self(), i);
			printf(
					"thread %lu, loop %d - item: messageType - %d, SEQ number - %ld\n",
					(long unsigned int)self(), i, item->TYPE, item->SEQ);
			delete item;
		}
		return NULL;
	}
};*/

void *fun(void* queue)
{
	wqueue<AlgoMsg*>*m_queue=(wqueue<AlgoMsg*>*)queue;

	// Remove 1 item at a time and process it. Blocks if no items are 
			// available to process.
			for (int i = 0;; i++) {
				printf("thread , loop %d - waiting for item...\n",i);
				AlgoMsg* item = m_queue->remove();
				printf("thread  loop %d - got one item\n", i);
				printf(
						"thread loop %d - item: messageType - %d, SEQ number - %ld\n", i, item->TYPE, item->SEQ);
				delete item;
			}
			return NULL;
}
int main() {

	AlgoMsg *message1;
	message1 = (struct AlgoMsg *)malloc(sizeof(struct AlgoMsg));
	message1->TYPE=1;
	message1->ORIGIN=2;
	message1->SEQ=12121;
	message1->sender=4;

	AlgoMsg *message2;
	message2 = (struct AlgoMsg *)malloc(sizeof(struct AlgoMsg));
	message2->TYPE=2;
	message2->ORIGIN=3;
	message2->SEQ=3232;
	message2->sender=5;
	communication c;

	wqueue<AlgoMsg*> queue;

	queue.add(message1);
	queue.add(message2);
	/*ConsumerThread* thread1 = new ConsumerThread(queue);
	thread1->start();*/
	pthread_t thread1;
	pthread_create(&thread1, NULL, fun,(void *)&queue);
	 
	while (queue.size() < 0)
		;
	pthread_join(thread1,NULL);
	printf("done\n");
	exit(0);

	/*	 	strcpy(c.dest_IP_Address,"10.176.67.65");
	 printf(c.dest_IP_Address);
	 c.dest_port=1235;
	 
	 c.sendMessage(message);*/
	return 0;
}
