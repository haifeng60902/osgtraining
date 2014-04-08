#ifndef _DECODE_FEEDBACK_H_
#define _DECODE_FEEDBACK_H_

#include "core/Parse/binMiner.h"

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

	/*
	tVecSummary vSummary;
	tVecPools vPools;
	tVecCoin vCoin;
	tVecDevs vDevs;
	*/
};

#endif	//_DECODE_FEEDBACK_H_