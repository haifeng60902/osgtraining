#ifndef _DECODE_FEEDBACK_H_
#define _DECODE_FEEDBACK_H_

#include "binMiner.h"

class decodeFeedback
{
public:
	decodeFeedback();
	~decodeFeedback();

	//decode string to binary data
	void parse(eMinerMode mode, const std::string& msg);

private:
	void decodeSummary(const std::string& msg);
	void decodePools(const std::string& msg);
	void decodeCoin(const std::string& msg);
	void decodeDevs(const std::string& msg);

	//helper func: parse str to some substr separated by "|" 
	void parseSubstr(const std::string& msg, tVecStr* vStr);

	int GetInt(const std::string& msg, const std::string& param);
	std::string GetStr(const std::string& msg, const std::string& param);
	double GetDouble(const std::string& msg, const std::string& param);
	bool BoolDetect(std::string sBool);
	/*
	tVecSummary vSummary;
	tVecPools vPools;
	tVecCoin vCoin;
	tVecDevs vDevs;
	*/
};

#endif	//_DECODE_FEEDBACK_H_