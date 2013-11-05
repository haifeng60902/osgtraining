#include "EmulLogic.h"

#include <string.h>
#include <string>
#include <iostream>

EmulLogic::EmulLogic()
{
	inSize=0;
	outSize=0;
}

EmulLogic::~EmulLogic()
{

}

void EmulLogic::Accumulate(const char* pBuff, int iSize)
{
	//данные могут приниматся частями
	memcpy(&inBuff[inSize], pBuff, iSize);
	inSize+=iSize;
}

void EmulLogic::Process()
{
	//обработать входные данные
	int iNameSize=inBuff[0];
	char name[256];
	memcpy(name, &inBuff[1], iNameSize);
	name[iNameSize]=0;
	std::string sName(name);

	int* pRes=(int*)(&inBuff[iNameSize+1]);

	std::cout<<"Node: "<<sName<<" Result:"<<(*pRes);

	inSize=0;
}

const char* EmulLogic::GetResult(int *pSize)
{
	//результат для отправки в сеть
	float fSleep=(float)rand()/(float)RAND_MAX;

	int iSleep=fSleep*1000;

	(*pSize)=sizeof(int);

	int* pSleep=(int*)(&outBuff[0]);
	(*pSleep)=iSleep;
	return outBuff;
}