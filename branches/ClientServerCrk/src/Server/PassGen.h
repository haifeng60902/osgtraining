#ifndef _PASS_GEN_H_
#define _PASS_GEN_H_

#include <string>
#include <vector>

#include "defs/binDefs.h"

class PassGen
{
public:
	PassGen();
	~PassGen();

	void Init(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase,
		int iPASS_IN_ONE_MSG, bool bReverse, int iPASS_START_LEN);

	//generate next password
	void GenNextPass(std::wstring* pPass, std::wstring* pCons);
	
	//generate next password with separate chain
	void GenNextChainPass(std::wstring* pPass, std::wstring* pCons, char* pChain, bool bZero);

	//save success password
	void SaveSuccessPass(const std::wstring& wConf);

	void Close(bool bSave);

	//get password state
	void GetPassState(char* pDest);

private:

	struct binConvert
	{
		binConvert():pos(0),
			num(1)
		{};
		int pos;
		int num;
	};

	typedef std::vector<binConvert> tVecConv;

	//сохранение состояния
	void SaveState();

	//состояние из файла
	void LoadState(int iPASS_START_LEN);

	//load config
	void LoadConf(const std::wstring& wConf, std::wstring* pPass, std::wstring* pCons, tVecConv *pConv);

	//is all elements zero
	bool ZeroChk(char* pDest); 

	std::wstring wPass;//for password
	std::wstring wCons;//for console output

	std::wstring wPhrasePass;//for password
	std::wstring wPhraseCons;//for console output

	std::wstring wSave;

	tVecConv vConvert;
	tVecConv vPhrareConv;

	char cPassState[MAX_LEN_PASS];

	int iAutosave;

	bool bFirstTime;

	int m_iPASS_IN_ONE_MSG;

	bool m_bReverse;
};

#endif	//_PASS_GEN_H_