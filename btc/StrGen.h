#ifndef _STR_GEN_H_
#define _STR_GEN_H_

#include <string>

class StrGen
{
public:
	StrGen();
	~StrGen();

	//считать правила перебора
	void LoadPassRule(const char *pFile);

	//следующая последовательность
	std::string GenNextStr();

private:
	
};

#endif	//_STR_GEN_H_