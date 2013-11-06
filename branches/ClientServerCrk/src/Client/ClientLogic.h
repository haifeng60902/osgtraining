#ifndef _CLIENT_LOGIC_H_
#define _CLIENT_LOGIC_H_

#include <string>
#include "Time/Timer.h"

#include "EmulLogic.h"
#include "PassChkLogic.h"

class TCPConnector;

class ClientLogic
{
public:
	ClientLogic();
	~ClientLogic();

	void Init(int iPort, const std::string& sAddress, const std::string& sNode);

	void Process();

	void Close();

private:
	//определение нажатия на клавиши
	bool KeyPressDetect();

	TCPConnector* pConnector;

	EmulLogic m_EmulLogic;
	PassChkLogic m_PassChkLogic;

	Timer m_Timer;

	int iPort;
	std::string sAddress;
	std::string sNode;
};

#endif	//_CLIENT_LOGIC_H_