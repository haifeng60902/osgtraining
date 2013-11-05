#ifndef _SERVER_LOGIC_H_
#define _SERVER_LOGIC_H_

#include <string>

#include "Time/Timer.h"
#include "EmulLogic.h"

class TCPAcceptor;

class ServerLogic
{
public:
	ServerLogic();
	~ServerLogic();

	void Init(int iPort, const std::string& sAddress);

	void Process();

	void Close();

private:
	//определение нажатия на клавиши
	bool KeyPressDetect();

	//logic emulator
	EmulLogic m_EmulLogic;

	Timer m_Timer;

	TCPAcceptor* pAcceptor;

	int iResult;

	char inBuff[8192];
};

#endif	//_SERVER_LOGIC_H_