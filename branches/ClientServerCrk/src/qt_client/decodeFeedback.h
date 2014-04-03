#ifndef _DECODE_FEEDBACK_H_
#define _DECODE_FEEDBACK_H_

#include "binMiner.h"

class decodeFeedback
{
public:
	decodeFeedback();
	~decodeFeedback();

	void decode(eMinerMode mode, const std::string& msg);

private:
	void decodeSummary(const std::string& msg);

	//helper func: parse str to some substr separated by "|" 
	void parseSubstr(const std::string& msg, tVecStr* vStr);

	int GetInt(const std::string& msg, const std::string& param);
	std::string GetStr(const std::string& msg, const std::string& param);
	float GetFloat(const std::string& msg, const std::string& param);

	tVecSummary vSummary;
};

#endif	//_DECODE_FEEDBACK_H_