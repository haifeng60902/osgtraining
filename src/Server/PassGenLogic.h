#ifndef _PASSGEN_LOGIC_H_
#define _PASSGEN_LOGIC_H_

#include "defs/binDefs.h"
#include "PassGen.h"

class PassGenLogic
{
public:
	PassGenLogic();
	~PassGenLogic();

	//pass generator logic init
	void InitPassLogic(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase);

	//прием данных
	void Accumulate(const char* pBuff, int iSize);

	//process income data
	bool Process();

	//результат для отправки в сеть
	const char* GetResult(int *pSize);

	//debug logic
	void TestLogic();

private:

	//read node name
	int DetectName(int pos);

	//read chain state
	int DetectChainState(int pos);

	//read result
	int DetectResult(int pos);

	//analayse data from network
	bool Analyse();

	//first client connect
	void ClientConnect();

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

	//the password is find
	void Success();

	PassGen m_PassGen;

	std::string sNode;

	char curChain[MAX_LEN_PASS];
	int iCurResult;

	//буфер для приема сообщений
	char inBuff[32768];
	int inSize;

	//результат
	char outBuff[32768];
	int outSize;
};

#endif	//_PASSGEN_LOGIC_H_