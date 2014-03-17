#include <iostream>

#include "Tcp/TCPConnector.h"

int main(int argc, char **argv)
{
	std::cout<<"ok\n";
	
	TCPConnector* pConnector;
	//std::string sStat("summary");
	std::string sStat("gpuvddc|0,1.0");
	pConnector=new TCPConnector();
	TCPStream* stream = pConnector->connect(	4028, "127.0.0.1");
	if (stream)
	{
		int iSize=sStat.length()+1;
		char pBuff[8196];
		
		memcpy(pBuff,sStat.c_str(), iSize);
		stream->send(pBuff, iSize);

		char inBuff[8196];
		int inSize=0;
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
		for (int i=0;i<inSize;++i)
		{
			std::cout<<inBuff[i];
		}
		std::cout<<"\n end \n";
	}
}