#include <iostream>

#include "Tcp/TCPConnector.h"

int main()
{
	char inBuff[8192];
	char outBuff[8192];

	TCPConnector* pConnector;
	pConnector=new TCPConnector();
	TCPStream* stream = pConnector->connect(8888, "178.124.147.154");
	if (stream)
	{
		stream->send(outBuff, 512);
		std::cout<<"send ok\n";

		int len=stream->receive(inBuff, sizeof(inBuff));

		std::cout<<"receive: "<<len<<"\n";

		delete stream;
	}

	std::cout<<"finish\n";
}