#ifndef _WIN_CREATE_PROCESS_H_
#define _WIN_CREATE_PROCESS_H_

#include "binClient.h"

class winCreateProcess
{
public:
	winCreateProcess();
	~winCreateProcess();

	bool create(int i, binClient& client);
};

#endif	//_WIN_CREATE_PROCESS_H_