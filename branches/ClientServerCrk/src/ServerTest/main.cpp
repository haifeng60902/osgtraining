#include <iostream>

#include "Tcp/TCPAcceptor.h"

int main()
{
	char inBuff[8192];
	char outBuff[8192];
	TCPAcceptor* pAcceptor;

	pAcceptor=new TCPAcceptor(8888, "");	//178.124.147.154
	pAcceptor->start();
	TCPStream* stream = pAcceptor->accept();

	if (stream)
	{
		int len=0;
		len = stream->receive(inBuff, sizeof(inBuff));

		std::cout<<"Get from net: "<<len<<"\n";

		stream->send(outBuff, 256);

		delete stream;
	}

	std::cout<<"finish\n";
}