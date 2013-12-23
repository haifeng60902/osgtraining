#ifndef _BAT_GEN_H_
#define _BAT_GEN_H_

#include <string>
#include "binHosts.h"

class BatGen
{
public:
	BatGen();
	~BatGen();

	bool Gen(const binHosts& mHost, const std::string& sPool);
};

#endif	//_BAT_GEN_H_