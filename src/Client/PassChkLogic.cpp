#include "PassChkLogic.h"

#include "defs/binDefs.h"
#include "Tcp/TCPStream.h"

PassChkLogic::PassChkLogic()
{

}

PassChkLogic::~PassChkLogic()
{

}

void PassChkLogic::Init(const std::string& sNode)
{
	//set node name
	this->sNode=sNode;

	//first time init output buffer
	FirstTimeInit();
}

void PassChkLogic::FirstTimeInit()
{
	//first time init output buffer
	int x=sNode.size();
	outBuff[0]=x;
	memcpy(&outBuff[1], sNode.c_str(), x);
	++x;
	memset(&outBuff[x], 0, MAX_LEN_PASS);
	x+=MAX_LEN_PASS;
	outBuff[x]=-1;
	++x;
	outSize=x;
}

const char* PassChkLogic::GetResult(int* pSize)
{
	//get result for network sending
	(*pSize)=outSize;
	return outBuff;
}

void PassChkLogic::Accumulate(TCPStream* stream)
{
	//wait server response
	inSize=0;
	bool bProc=true;
	while(bProc)
	{
		int len=stream->receive(inBuff, sizeof(inBuff));
		if (len)
		{
			inSize=len;

			//данные получены, можно выходить
			bProc=false;
		}
	}
}

void PassChkLogic::Process()
{
	//process income data

}