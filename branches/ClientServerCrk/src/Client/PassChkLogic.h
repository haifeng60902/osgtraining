#ifndef _PASS_CHK_LOGIC_H_
#define _PASS_CHK_LOGIC_H_

#include <string>

#include "BtcdLauncher.h"

class PassChkLogic
{
public:
	PassChkLogic();
	~PassChkLogic();

	//set node name
	void Init(const std::string& sNode);

private:

	//first time init output buffer
	void FirstTimeInit();
	
	std::string sNode;

	BtcdLauncher m_BtcdLauncher;

	//буфер для приема сообщений
	char inBuff[32768];
	int inSize;

	//результат
	char outBuff[32768];
	int outSize;
};

#endif	//_PASS_CHK_LOGIC_H_