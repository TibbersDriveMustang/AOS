#pragma once
class MessageBox
{
public:
	MessageBox(void);
	~MessageBox(void);
	struct AlgoMsg{
		int TYPE;
		int ORIGIN;
		long SEQ;
		int sender;
	}
};

