#ifndef _CORE_PARSE_H_
#define _CORE_PARSE_H_

#include <string>
#include <vector>

typedef std::vector<std::string> tVecStr;

namespace Parse
{
	//helper func: parse str to some substr separated by "|" 
	void Substr(const std::string& msg, tVecStr* vStr);

	int GetInt(const std::string& msg, const std::string& param);
	std::string GetStr(const std::string& msg, const std::string& param);
	double GetDouble(const std::string& msg, const std::string& param);
	bool BoolDetect(std::string sBool);
}

#endif	//_CORE_PARSE_H_