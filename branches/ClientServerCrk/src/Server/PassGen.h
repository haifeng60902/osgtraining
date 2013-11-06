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

	void Init(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase);

	//generate next password
	void GenNextPass(std::wstring* pPass, std::wstring* pCons);

	//save success password
	void SaveSuccessPass(const std::wstring& wConf);

	void Close(bool bSave);

	//get password state
	void GetPassState(char* pDest);

	//get exact password
	void GetCurrentPass(char* pDest, int iPos, std::wstring* pPass, std::wstring* pCons);

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
	void LoadState();

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
};

#endif	//_PASS_GEN_H_