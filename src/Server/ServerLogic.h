#ifndef _SERVER_LOGIC_H_
#define _SERVER_LOGIC_H_

#include <string>

#include "Time/Timer.h"
#include "PassGenLogic.h"

class TCPAcceptor;

class ServerLogic
{
public:
	ServerLogic();
	~ServerLogic();

	void Init(int iPort, const std::string& sAddress);

	//pass generator logic init
	void InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase, 
		float fTimeout, int iPASS_IN_ONE_MSG, bool bReverse=false);

	void Process();

	void Close();

private:
	//key press detect
	bool KeyPressDetect();

	//real logic
	PassGenLogic m_PassGenLogic;

	Timer m_Timer;

	TCPAcceptor* pAcceptor;

	int iResult;

	char inBuff[8192];
};

#endif	//_SERVER_LOGIC_H_