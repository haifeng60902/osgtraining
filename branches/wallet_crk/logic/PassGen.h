#ifndef _PASS_GEN_H_
#define _PASS_GEN_H_

#include <string>

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

	void Close();
};

#endif	//_PASS_GEN_H_