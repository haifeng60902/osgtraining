#include "StrGen.h"

#include <fstream>

StrGen::StrGen()
{

}

StrGen::~StrGen()
{

}

std::string StrGen::GenNextStr()
{
	//��������� ������������������
	return std::string("null");
}

void StrGen::LoadPassRule(const char *pFile)
{
	//������� ������� ��������
	std::ifstream ifs(pFile);
	while(!ifs.eof())
	{
		std::string line;
		std::getline(ifs,line);
		//cout << "[ " << line << " ]" << endl;
	}
}