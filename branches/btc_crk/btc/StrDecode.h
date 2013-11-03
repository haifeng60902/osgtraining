#ifndef _STR_DECODE_H_
#define _STR_DECODE_H_

#include <string>
#include "binDecode.h"

class StrDecode
{
public:
	StrDecode();
	~StrDecode();

	//считать правила преобразования символов
	void LoadTable(const char *pFile);

	//загрузить последний прерванный сеанс
	void LoadLastSave(const char* pFile);

	//следующая последовательность
	std::string GenNextStr();

private:
	std::string TryStr(int iL, int iO);

	tMapDecode m_Decode;//для преобразования
	tVecStr m_VecStr;	//исходный пароль

	int m_iI;	//номер попытки
};

#endif	//_STR_DECODE_H_