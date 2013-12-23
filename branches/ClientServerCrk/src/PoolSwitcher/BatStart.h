#ifndef _BAT_START_H_
#define _BAT_START_H_

#include "binHosts.h"

class BatStart
{
public:
	BatStart();
	~BatStart();

	void Process(const tVecHosts& vHost);

private:
	void PsStart(const std::string& sExe, const std::string& sParam);
};

#endif	//_BAT_START_H_