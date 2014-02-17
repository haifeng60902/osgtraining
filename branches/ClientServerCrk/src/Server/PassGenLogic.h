#ifndef _PASSGEN_LOGIC_H_
#define _PASSGEN_LOGIC_H_

#include <map>
#include <string>

#include "defs/binDefs.h"
#include "PassGen.h"

class PassGenLogic
{
public:
	PassGenLogic();
	~PassGenLogic();

	//pass generator logic init
	void InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase
		, float fTimeout, int iPASS_IN_ONE_MSG, bool bReverse, int iPASS_START_LEN);

	//get data from net
	void Accumulate(const char* pBuff, int iSize);

	//process income data
	bool Process(float fTime);

	//get data for network
	const char* GetResult(int *pSize);

	//node name connected
	std::string GetNodeName(){return sNode;};

	//debug logic
	void TestLogic();

private:

	//key - file name, value - create time
	typedef std::map<std::string,float> tMapFileTime;

	//read node name
	int DetectName(int pos);

	//read chain state
	int DetectChainState(int pos);

	//read result
	int DetectResult(int pos);

	//analayse data from network
	bool Analyse(float fTime);

	//client connect
	void ClientConnect(float fTime);

	//client do not find password
	void ClientDoNotFindPass();

	//generate file name
	std::string GenFileName(char* pChain);

	//debug logic
	void TestFillInBuff();

	//fill output buffer
	void FillOutBuff(char* pChain, const tVecWStr& vPass, const tVecWStr& vCons);

	//restore output buffer(for test purpose)
	void RestoreRawMemory(tVecWStr& vPassChk, tVecWStr& vConsChk);

	//check result code-decode
	void CheckCodeDecode(const tVecWStr& vPass, const tVecWStr& vCons);

	//write to file network output buffer
	void Write2File(const std::string& sFile);

	//check zero chain
	bool ZerroChainDetect(const char* pChain);

	//the password is find
	void Success();

	//read files from previous start
	void ReadPreviousFiles();

	//check files
	bool CheckMapFileTime(float fTime);

	//display performance
	void LogPerfomance(float fTime);

	PassGen m_PassGen;

	std::string sNode;

	//for password time control
	tMapFileTime m_mFileTime;

	char curChain[MAX_LEN_PASS];
	int iCurResult;

	//max time for disconnected client
	float m_fTimeout;

	//буфер для приема сообщений
	//buffer for in
	char inBuff[32768];
	int inSize;

	//result
	char outBuff[32768];
	int outSize;

	float m_fPrevTime;
	int m_iSumPass;

	int m_iPASS_IN_ONE_MSG;
};

#endif	//_PASSGEN_LOGIC_H_