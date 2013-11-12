//============================================================================
// Name        : aos1.cpp
// Author      : kaushik sirineni
// Version     :
// Copyright   : all rights reserved @ kaushik.me
// Description : Mutual Exclusion
//============================================================================

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "communication.h"
#include "Starter.h"

using namespace std;
char *str = "hello";

void *fun(void*)
{
	printf("in thead\n");
	printf("%s",str);
	return NULL;
}
/*
int main() {
	cout << "Mutual Exclusion" << endl; // prints Mutual Exclusion

	pthread_t *threads;
	int noOfThreads = 2;
	 threads = (pthread_t*)malloc(sizeof(pthread_t) * noOfThreads);
	if (NULL != threads)
	{

		for (int i=0;i<noOfThreads;i++)
		{
			 pthread_create(&threads[i], NULL, fun, NULL);
		}

		for (int i=0;i<noOfThreads;i++)
		{
			pthread_join(threads[i],NULL);


		}
	}
	else
	{
		cout<<"Cant create threads";
	}

	int z;
		char buf[32];
		z = gethostname(buf,sizeof buf);
		if ( z == -1 ) {
			fprintf(stderr, "%s: gethostname(2)\n",
			strerror(errno));
			exit(1);
		}

		printf("hostname: %s\n",buf);

		Starter s;
		s.init();
	return 0;
}
/**/


