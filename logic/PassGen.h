#ifndef _PASS_GEN_H_
#define _PASS_GEN_H_

#include <string>
#include <vector>

#define MAX_PASS 20

class PassGen
{
public:
	PassGen();
	~PassGen();

	void Init(const std::wstring& wConf, const std::wstring& wAutosave, const std::wstring& wPhrase);

	//generate next password
	std::wstring GenNextPass();

	//save success password
	void SaveSuccessPass(const std::wstring& wConf);

	void Close(bool bSave);

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

	std::wstring wPass;//for password
	std::wstring wCons;//for console output

	std::wstring wPhrasePass;//for password
	std::wstring wPhraseCons;//for console output

	std::wstring wSave;

	tVecConv vConvert;
	tVecConv vPhrareConv;

	int iPassState[MAX_PASS];

	int iAutosave;

	bool bFirstTime;
};

#endif	//_PASS_GEN_H_