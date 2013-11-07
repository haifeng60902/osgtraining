#ifndef _CLIENT_LOGIC_H_
#define _CLIENT_LOGIC_H_

#include <string>
#include "Time/Timer.h"

#include "PassChkLogic.h"

class TCPConnector;

class ClientLogic
{
public:
	ClientLogic();
	~ClientLogic();

	bool Init(int iPort, const std::string& sAddress, const std::string& sNode);

	void Process();

	void Close();

private:
	//определение нажатия на клавиши
	bool KeyPressDetect();

	TCPConnector* pConnector;

	PassChkLogic m_PassChkLogic;

	Timer m_Timer;

	int iPort;
	std::string sAddress;
	std::string sNode;

	int iSuccess;
};

#endif	//_CLIENT_LOGIC_H_