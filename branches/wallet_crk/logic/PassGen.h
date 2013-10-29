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

	void Init(const std::wstring& wConf, const std::wstring& wAutosave);

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

	//сохранение состояния
	void SaveState();

	//состояние из файла
	void LoadState();

	//load config
	void LoadConf(const std::wstring& wConf);

	std::wstring wPass;//for password
	std::wstring wCons;//for console output

	std::wstring wSave;

	std::vector<binConvert> vConvert;

	int iPassState[MAX_PASS];

	int iAutosave;
};

#endif	//_PASS_GEN_H_