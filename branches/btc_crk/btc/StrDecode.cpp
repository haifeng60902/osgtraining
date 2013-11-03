#include "StrDecode.h"

#include <fstream>
#include <sstream>

StrDecode::StrDecode()
{
	m_iI=0;
}

StrDecode::~StrDecode()
{

}

void StrDecode::LoadTable(const char *pFile)
{
	//считать правила преобразования символов
	std::ifstream ifs(pFile);
	while(!ifs.eof())
	{
		std::string line;
		std::getline(ifs, line);
		if (!line.empty())
		{
			unsigned char c0=line[0];
			unsigned char c1=line[2];
			unsigned char c2=line[4];
			unsigned char c3=line[6];

			m_Decode[c0].push_back(c1);
			m_Decode[c0].push_back(c2);
			m_Decode[c0].push_back(c3);
		}
	}
}

void StrDecode::LoadLastSave(const char* pFile)
{
	//загрузить последний прерванный сеанс
	std::ifstream ifs(pFile);
	int i=0;
	while(!ifs.eof())
	{
		std::string line;
		std::getline(ifs,line);
		m_VecStr.push_back(line);
	}
}

std::string StrDecode::GenNextStr()
{
	//следующая последовательность
	int iL=m_iI/4;
	int iO=m_iI%4;

	++m_iI;

	if (iL<m_VecStr.size())
	{
		if (iO==0)
			return m_VecStr[iL];
		else
			return TryStr(iL, iO);
	}

	return std::string("");
}

std::string StrDecode::TryStr(int iL, int iO)
{
	std::string sRes;
	for (int i=0;i<m_VecStr[iL].size();++i)
	{
		unsigned char c=m_VecStr[iL][i];
		sRes.push_back(m_Decode[c][iO-1]);
	}

	return sRes;
}