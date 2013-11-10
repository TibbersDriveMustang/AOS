#include<stdio.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "communication.h"


void *fun(void*)
{
	communication com;
	com.serverListen(1235);
	return NULL;
}

int main()
{
	pthread_t thread2;
	
	/* thread1 = (pthread_t*)malloc(sizeof(pthread_t));*/
	 pthread_create(&thread2, NULL, fun, NULL);
	 pthread_join(thread2,NULL);
	 	return 0;
}