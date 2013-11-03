#ifndef _STR_DECODE_H_
#define _STR_DECODE_H_

#include <string>
#include "binDecode.h"

class StrDecode
{
public:
	StrDecode();
	~StrDecode();

	//������� ������� �������������� ��������
	void LoadTable(const char *pFile);

	//��������� ��������� ���������� �����
	void LoadLastSave(const char* pFile);

	//��������� ������������������
	std::string GenNextStr();

private:
	std::string TryStr(int iL, int iO);

	tMapDecode m_Decode;//��� ��������������
	tVecStr m_VecStr;	//�������� ������

	int m_iI;	//����� �������
};

#endif	//_STR_DECODE_H_