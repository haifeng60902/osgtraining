#ifndef _FIRST_PASS_H_
#define _FIRST_PASS_H_

#include "binInput.h"

class FirstPass
{
public:
	FirstPass();
	~FirstPass();

	void Init(const binInput& in);

	void Save();

private:

	//заполнить вектор хэшей
	void FillHashVec();

	//сгенерить текст батника
	void GenBatFirst();
	void GenBatRestore();

	const binInput* pIn;

	tVecStr vHash;

	std::string sResFirst;
	std::string sResRestore;
};

#endif	//_FIRST_PASS_H_