#ifndef _BIN_INPUT_H_
#define _BIN_INPUT_H_

#include <string>
#include <vector>

struct binInput
{
	binInput():runTime(600),
		statusTime(60),
		restoreTime(30),
		passFile("pass.txt")
	{};
	std::string exeFile;				//имя exe файла
	std::string hashFile;				//имя файла с хэшами
	std::string passFile;	//выходной файл с паролями
	int runTime;					//время в секундах на запись
	int statusTime;					//выводить статус через каждые (сек)
	int restoreTime;					//сохранять статус каждые (сек)
};

typedef std::vector<std::string> tVecStr;

#endif	//_BIN_INPUT_H_