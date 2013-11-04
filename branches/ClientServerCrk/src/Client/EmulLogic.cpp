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
	bool bNet=false;
	while(bProc)
	{
		int len=stream->receive(inBuffTmp, sizeof(inBuffTmp));
		if (len)
		{
			memcpy(&inBuff[inSize], inBuffTmp, len);
			inSize+=len;
			bNet=true;
		}

		if ((len==0)&&(bNet))
			//данные получены, можно выходить
			bProc=false;
	}
}

void EmulLogic::Process()
{
	//обработать входные данные
	int* pDelay=(int*)(&inBuff[0]);
	
	std::cout<<(*pDelay)<<" ";
	Sleep((*pDelay));
	
	outBuff[0]=sNode.size();
	memcpy(&outBuff[1], sNode.c_str(), sNode.size());
	int *Res=(int*)(&outBuff[1+sNode.size()]);
	(*Res)=(*pDelay);

	outSize=sNode.size()+1+sizeof(int);
}