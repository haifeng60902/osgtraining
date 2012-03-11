#ifndef _STR_GEN_H_
#define _STR_GEN_H_

#include <string>
#include "binStr.h"

class StrGen
{
public:
	StrGen();
	~StrGen();

	//считать правила перебора
	void LoadPassRule(const char *pFile);

	//следующая последовательность
	std::string GenNextStr();

	//сохранить в файл текущую строку
	void SaveResult();

	//загрузить последний прерванный сеанс
	void LoadLastSave(const char* pFile);

private:

	//перейти к следующей последовательности
	void IncreaseSymbol();

	//сформировать строку
	std::string GenStr();

	//сохранить промежуточный результат
	void SaveProcess();

	//символы для подстановки
	tVVecUChar m_vvUChar;

	//счетчик символов
	tVecUChar m_vCount;

	//признак конца вариантов
	bool m_bEnd;
};

#endif	//_STR_GEN_H_