#include "test_hlp.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "QtHlp/QtHlp.h"

test_hlp::test_hlp()
{

}

test_hlp::~test_hlp()
{

}

void test_hlp::check()
{
	int iChk=0;
	bool bRes=true;
	while(bRes)
	{
		int size=1+(float)rand()/(float)RAND_MAX*4;
		std::vector<std::string> vStr;
		vStr.resize(size);

		//fill rand strings
		for(int i=0;i<size;++i)
			QtHlp::rndStr(&vStr[i],1024,2048);

		
		std::vector<char> data;

		//convert from vector strings to vector char data
		QtHlp::WriteStrs(vStr, data);
		
		std::vector<std::string> vStrChk;
		
		//convert from char data to vector strings
		QtHlp::GetStrs(data.size(), &data[0], &vStrChk);
		
		if(vStrChk.size()==vStr.size())
		{
			for (int i=0;i<vStr.size();++i)
				if (vStrChk[i].compare(vStr[i])!=0)
					bRes=false;
		}
		else
			bRes=false;


		std::cout<<iChk<<" ";

		++iChk;
	}
}