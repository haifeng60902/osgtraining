#ifndef _LOG_INFO_H_
#define _LOG_INFO_H_

#define LOG2CONSOLE
#define LOG2FILE

#include "Singleton.h"

#include <iostream>
#include <fstream>
#include <map>

class LogInfo : public Singleton< LogInfo >
{
public:
	LogInfo();
	~LogInfo();

	//добавить сообщение в log
	void Print(std::string _str);

	//добавить сообщение в log
	void Print(const char *module, int level, const char *fmt, va_list args);

private:

#ifdef LOG2FILE
	std::ofstream m_out;
#endif

#ifdef LOG2FILE	|| LOG2CONSOLE
	std::map<int, std::string> m_mLog;
#endif
};

#endif	//_LOG_INFO_H_