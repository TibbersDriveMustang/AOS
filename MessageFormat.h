#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H

#pragma once


	typedef struct AlgoMsg{
		int TYPE; // 0: request_token, 1: have-token, 2: release, 3:send-token
		int ORIGIN;
		long SEQ;
		int sender;
	}messagetype;


#endif
