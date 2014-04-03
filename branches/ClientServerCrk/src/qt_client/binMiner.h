#ifndef _BIN_MINER_H_
#define _BIN_MINER_H_

#include <ctime>
#include <map>
#include <vector>

enum eMinerMode
{
	enFirtMsg,
	enSummary,
	enPools,
	enCoin,
	enQuit
};

typedef std::map<eMinerMode, std::string> tMode2Str;

struct binSummary
{
	time_t tTime;
	std::string sDesc;
	int iElapsed;
	float fMHSav;
	float fMHS5s;
	int iFoundBlocks;
	int iGetworks;
	int iAccepted;
	int iRejected;
	int iHardwareErrors;
	float fUtility;
	int iDiscarded;
	int iStale;
	int iGetFailures;
	int iLocalWork;
	int iRemoteFailures;
	int iNetworkBlocks;
	float fTotalMH;
	float fWorkUtility;
	float fDifficultyAccepted;
	float fDifficultyRejected;
	float fDifficultyStale;
	int iBestShare;
	float fDeviceHardware;
	float fDeviceRejected;
	float fPoolRejected;
	float fPoolStale;
};

typedef std::vector<binSummary> tVecSummary;

typedef std::vector<std::string> tVecStr;

#endif	//_BIN_MINER_H_