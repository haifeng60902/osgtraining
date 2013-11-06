#ifndef _PASS_CHK_LOGIC_H_
#define _PASS_CHK_LOGIC_H_

#include <string>

#include "BtcdLauncher.h"

class TCPStream;

class PassChkLogic
{
public:
	PassChkLogic();
	~PassChkLogic();

	//set node name
	void Init(const std::string& sNode);

	//get result for network sending
	const char* GetResult(int* pSize);

	//wait server response
	void Accumulate(TCPStream* stream);

	//process income data
	void Process();

private:

	//first time init output buffer
	void FirstTimeInit();
	
	std::string sNode;

	BtcdLauncher m_BtcdLauncher;

	//����� ��� ������ ���������
	char inBuff[32768];
	int inSize;

	//���������
	char outBuff[32768];
	int outSize;
};

#endif	//_PASS_CHK_LOGIC_H_