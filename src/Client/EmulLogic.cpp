#include "EmulLogic.h"

#include <iostream>
#include "Tcp/TCPStream.h"

EmulLogic::EmulLogic()
{
	inSize=0;
}

EmulLogic::~EmulLogic()
{

}

void EmulLogic::Init(const std::string& sNode)
{
	this->sNode=sNode;

	//заполнить выходной буфер
	FillOutBuffer(-1);
}

const char* EmulLogic::GetResult(int* pSize)
{
	//результат для отправки
	(*pSize)=outSize;
	return outBuff;
}

void EmulLogic::Accumulate(TCPStream* stream)
{
	//получить ответ от сервера
	inSize=0;
	bool bProc=true;
	while(bProc)
	{
		int len=stream->receive(inBuffTmp, sizeof(inBuffTmp));
		if (len)
		{
			memcpy(&inBuff[inSize], inBuffTmp, len);
			inSize=len;
			
			//данные получены, можно выходить
			bProc=false;
		}
	}
}

void EmulLogic::Process()
{
	//обработать входные данные
	int* pDelay=(int*)(&inBuff[0]);
	
	std::cout<<(*pDelay)<<std::endl;
	Sleep((*pDelay));
	
	//заполнить выходной буфер
	FillOutBuffer((*pDelay));
}

void EmulLogic::FillOutBuffer(int i)
{
	//заполнить выходной буфер
	outBuff[0]=sNode.size();
	memcpy(&outBuff[1], sNode.c_str(), sNode.size());
	int *Res=(int*)(&outBuff[1+sNode.size()]);
	(*Res)=i;

	outSize=sNode.size()+1+sizeof(int);
}