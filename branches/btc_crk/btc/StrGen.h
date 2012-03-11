#ifndef _STR_GEN_H_
#define _STR_GEN_H_

#include <string>
#include "binStr.h"

class StrGen
{
public:
	StrGen();
	~StrGen();

	//������� ������� ��������
	void LoadPassRule(const char *pFile);

	//��������� ������������������
	std::string GenNextStr();

	//��������� � ���� ������� ������
	void SaveResult();

	//��������� ��������� ���������� �����
	void LoadLastSave(const char* pFile);

private:

	//������� � ��������� ������������������
	void IncreaseSymbol();

	//������������ ������
	std::string GenStr();

	//��������� ������������� ���������
	void SaveProcess();

	//������� ��� �����������
	tVVecUChar m_vvUChar;

	//������� ��������
	tVecUChar m_vCount;

	//������� ����� ���������
	bool m_bEnd;
};

#endif	//_STR_GEN_H_