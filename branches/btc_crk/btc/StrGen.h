#ifndef _STR_GEN_H_
#define _STR_GEN_H_

#include <string>

class StrGen
{
public:
	StrGen();
	~StrGen();

	//������� ������� ��������
	void LoadPassRule(const char *pFile);

	//��������� ������������������
	std::string GenNextStr();

private:
	
};

#endif	//_STR_GEN_H_