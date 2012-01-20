#ifndef _LOG_INFO_H_
#define _LOG_INFO_H_

#define LOG2CONSOLE
#define LOG2FILE

#include "Singleton.h"

#include <iostream>
#include <fstream>

class LogInfo : public Singleton< LogInfo >
{
public:
	LogInfo();
	~LogInfo();

	//добавить сообщение в log
	void Print( std::string _str );

private:

#ifdef LOG2FILE
	std::ofstream m_out;
#endif
};

#endif	//_LOG_INFO_H_