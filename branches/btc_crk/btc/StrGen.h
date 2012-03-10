#ifndef _STR_GEN_H_
#define _STR_GEN_H_

#include <string>

class StrGen
{
public:
	StrGen();
	~StrGen();

	//следующая последовательность
	std::string GenNextStr();
};

#endif	//_STR_GEN_H_