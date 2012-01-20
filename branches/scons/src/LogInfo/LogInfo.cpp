#include "LogInfo.h"

LogInfo::LogInfo()
{
#ifdef LOG2FILE
	m_out.open( "info.log" , std::ios::out | std::ios::binary );
#endif
}

LogInfo::~LogInfo()
{
#ifdef LOG2FILE
	m_out.close();
#endif
}

void LogInfo::Print( std::string _str )
{
	//добавить сообщение в log
#ifdef LOG2FILE	
	m_out << _str.c_str();
#endif

#ifdef LOG2CONSOLE
	std::cout << _str.c_str();
#endif
}