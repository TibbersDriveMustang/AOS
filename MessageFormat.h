#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H

#pragma once

#define REQUEST 0
#define HAVE_TOKEN 1
#define RELEASE 2
#define SEND_TOKEN 3

	/*struct AlgoMsg{
		int TYPE; // 0: request_token, 1: have-token, 2: release, 3:send-token
		int ORIGIN;
		long SEQ;
		int sender;
	};*/
	
	struct Packet{
		int TYPE; // 0: request_token, 1: have-token, 2: release, 3:send-token
		int ORIGIN;
		long SEQ;
		int sender;
	}__attribute__((packed));

#endif
