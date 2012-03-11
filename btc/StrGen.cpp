#include "StrGen.h"

#include <fstream>
#include <sstream>

StrGen::StrGen()
{
	m_bEnd=false;
}

StrGen::~StrGen()
{

}

std::string StrGen::GenNextStr()
{
	//следующая последовательность
	
	//перейти к следующей последовательности

	if (m_bEnd)
		return std::string("");

	IncreaseSymbol();

	if (m_bEnd)
		return std::string("");

	//сформировать строку
	return GenStr();
}

void StrGen::LoadPassRule(const char *pFile)
{
	//считать правила перебора
	std::ifstream ifs(pFile);
	int iL=0;
	while(!ifs.eof())
	{
		std::string line;
		std::getline(ifs,line);
		if (!line.empty())
		{
			m_vvUChar.resize(iL+1);
			for (int i=0;i<line.size();++i)
				m_vvUChar[iL].push_back(line[i]);
			++iL;
		}
	}

	if (!m_vvUChar.empty())
	{
		m_vCount.resize(m_vvUChar.size());
		for (int i=0;i<m_vvUChar.size();++i)
			m_vCount[i]=0;
	}
}

void StrGen::SaveResult()
{
	//сохранить в файл текущую строку
	std::string sStr=GenStr();

	std::ofstream m_out;
	m_out.open("pass.txt", std::ios::out|std::ios::binary);
	m_out<<sStr;
	m_out.close();
}

void StrGen::IncreaseSymbol()
{
	//перейти к следующей последовательности
	bool bC=true;
	int i=0;
	while(bC)
	{
		++m_vCount[i];
		if (m_vCount[i]>m_vvUChar[i].size())
		{
			m_vCount[i]=1;
			++i;
			if (i==m_vCount.size())
			{
				m_bEnd=true;
				bC=false;
			}
		}
		else
			bC=false;
	}

	//сохранить промежуточный результат
	SaveProcess();
}

std::string StrGen::GenStr()
{
	//сформировать строку
	std::string sRes;
	for (int i=0;i<m_vCount.size();++i)
	{
		if (m_vCount[i]>0)
			sRes.push_back(m_vvUChar[i][m_vCount[i]-1]);
	}

	return sRes;
}

void StrGen::SaveProcess()
{
//сохранить промежуточный результат
	std::ofstream m_out;
	m_out.open("process.txt", std::ios::out|std::ios::binary);

	for (int i=0;i<m_vCount.size();++i)
	{
		std::stringstream ss;
		ss<<(int)m_vCount[i];
		std::string sN(ss.str());
		m_out<<sN<<"\n";	
	}
	m_out.close();
}

void StrGen::LoadLastSave(const char* pFile)
{
	//загрузить последний прерванный сеанс
	std::ifstream ifs(pFile);
	int i=0;
	while(!ifs.eof())
	{
		int iI=0;
		ifs>>iI;
		m_vCount[i]=iI;
		++i;
		if (i==m_vCount.size())
			break;
		//std::string line;
		//std::getline(ifs,line);
	}
}