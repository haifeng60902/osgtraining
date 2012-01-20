#include "LogInfo.h"

#include <stdarg.h>
#include <sstream>

LogInfo::LogInfo()
{
#ifdef LOG2FILE
	m_out.open("tmp/info.log", std::ios::out | std::ios::binary);
#endif

#ifdef LOG2FILE	|| LOG2CONSOLE
	m_mLog[1]="ALERT";
	m_mLog[8]="ERROR";
	m_mLog[16]="WARNING";
	m_mLog[64]="INFO";
	m_mLog[128]="DEBUG";
	m_mLog[256]="TRACE";
#endif
}

LogInfo::~LogInfo()
{
#ifdef LOG2FILE
	m_out.close();
#endif
}

void LogInfo::Print(std::string _str)
{
	//добавить сообщение в log
#ifdef LOG2FILE	
	m_out << _str.c_str();
#endif

#ifdef LOG2CONSOLE
	std::cout << _str.c_str();
#endif
}

void LogInfo::Print(const char *module, int level, const char *fmt, va_list args)
{
	//добавить сообщение в log
#ifdef LOG2FILE	|| LOG2CONSOLE

	char buffer [512];
	sprintf(buffer,fmt, *((va_list*)args));
	
	std::stringstream ss;
	ss<<buffer<<"\n";

#ifdef LOG2FILE	
	m_out<<module<<"\t"<<m_mLog[level]<<"\t"<<ss.str()<<"\n";
#endif	//LOG2FILE

#ifdef LOG2CONSOLE
	std::cout<<module<<"\t"<<m_mLog[level]<<"\t"<<ss.str()<<"\n";
#endif	//LOG2CONSOLE

#endif	//LOG2FILE	|| LOG2CONSOLE
}