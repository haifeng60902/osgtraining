#ifndef _BIN_MINER_H_
#define _BIN_MINER_H_

#include <ctime>
#include <map>
#include <vector>

#define DISCONNECT_WAIT 10

enum eMinerMode
{
	enFirtMsg,
	enSummary,
	enPools,
	enCoin,
	enDevs,
	enQuit
};

typedef std::map<eMinerMode, std::string> tMode2Str;

//////////////////////////////////////////////////////////////////////////
//summary
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

//////////////////////////////////////////////////////////////////////////
//pools
struct binPool
{
	int iPOOL;
	std::string sURL;
	std::string sStatus;
	int iPriority;
	int iQuota;
	std::string sLongPoll;
	int iGetworks;
	int iAccepted;
	int iRejected;
	int iWorks;
	int iDiscarded;
	int iStale;
	int iGetFailures;
	int iRemoteFailures;
	std::string sUser;
	time_t tLastShareTime;
	int iDiff1Shares;
	std::string sProxyType;
	std::string sProxy;
	float fDifficultyAccepted;
	float fDifficultyRejected;
	float fDifficultyStale;
	float fLastShareDifficulty;
	bool bHasStratum;
	bool bStratumActive;
	std::string sStratumURL;
	bool bHasGBT;
	int iBestShare;
	float fPoolRejected;
	float fPoolStale;
};

typedef std::vector<binPool> tVecPool;

struct binPools
{
	time_t tTime;
	std::string sDesc;
	tVecPool vPool;
};

typedef std::vector<binPools> tVecPools;

//////////////////////////////////////////////////////////////////////////
//coin
struct binCoin
{
	time_t tTime;
	std::string sDesc;
	std::string sHashMethod;
	double dCurrentBlockTime;
	std::string sCurrentBlockHash;
	bool bLP;
	float fNetworkDifficulty;
};

typedef std::vector<binCoin> tVecCoin;

//////////////////////////////////////////////////////////////////////////
//devs
struct binGpu
{
	int iGPU;
	std::string sEnabled;
	std::string sStatus;
	float fTemperature;
	int iFanSpeed;
	int iFanPercent;
	int iGPUClock;
	int iMemoryClock;
	float fGPUVoltage;
	int iGPUActivity;
	int iPowertune;
	float fMHSav;
	float fMHS5s;
	int iAccepted;
	int iRejected;
	int iHardwareErrors;
	float fUtility;
	int iIntensity;
	time_t tLastSharePool;
	time_t tLastShareTime;
	float fTotalMH;
	int iDiff1Work;
	float fDifficultyAccepted;
	float fDifficultyRejected;
	float fLastShareDifficulty;
	time_t tLastValidWork;
	float fDeviceHardware;
	float fDeviceRejected;
	int iDeviceElapsed;
};

typedef std::vector<binGpu> tVecGpu;

struct binDevs
{
	time_t tTime;
	std::string sDesc;
	tVecGpu vGpu;
};

typedef std::vector<binDevs> tVecDevs;

typedef std::vector<std::string> tVecStr;

#endif	//_BIN_MINER_H_