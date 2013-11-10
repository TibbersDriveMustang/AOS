#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<string>
#include<errno.h>
#include <errno.h>
#include "MessageFormat.h"
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 32   /* Size of receive buffer */

using namespace std;


class communication {
public:
	char dest_IP_Address[13];
	string source_IP_Address;
	int dest_port;

	int sendMessage(struct Packet message);
	int serverListen(int portNum);

};


#endif /*COMMUNICATION_H_*/
