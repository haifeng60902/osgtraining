#ifndef _PASS_CHK_LOGIC_H_
#define _PASS_CHK_LOGIC_H_

#include <string>

#include "defs/binDefs.h"
#include "BtcdLauncher.h"

class TCPStream;

class PassChkLogic
{
public:
	PassChkLogic();
	~PassChkLogic();

	//set node name
	bool Init(const std::string& sNode);

	//get result for network sending
	const char* GetResult(int* pSize);

	//wait server response
	void Accumulate(TCPStream* stream);

	//process income data
	int Process();

private:

	//first time init output buffer
	void FirstTimeInit();

	//fill output buffer with results
	void FillOutBuffer(int iRes);

	//restore data from input buffer
	void RestoreRawMemory(tVecWStr& vPass, tVecWStr& vCons);

	//try unlock wallet
	int TryPass(const tVecWStr& vPass, const tVecWStr& vCons);

	//is bitcoind lunch like a daemon?
	bool BtcdDetect();
	
	std::string sNode;

	BtcdLauncher m_BtcdLauncher;

	//буфер для приема сообщений
	char inBuff[32768];
	int inSize;

	//результат
	char outBuff[32768];
	int outSize;

	char cChain[MAX_LEN_PASS];
};

#endif	//_PASS_CHK_LOGIC_H_