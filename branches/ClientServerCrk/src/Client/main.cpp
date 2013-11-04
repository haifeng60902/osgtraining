#include <iostream>

#include "Core/Lua/Lua_vm.h"
#include "Tcp/TCPConnector.h"

std::string sAddress("127.0.0.1");
int iPort=9999;

int main(int argc, char **argv)
{
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-config") == 0)
		{
			i++; if (i >= argc) break;
			Lua_vm lvm(argv[i]);
			sAddress=lvm.get_string("address");
			iPort=lvm.get_int("port");
			continue;
		}
	}

	TCPConnector connector;
	TCPStream* stream = connector.connect(iPort, sAddress.c_str());

	if (stream)
	{
		std::string message = "Is there life on Mars?";
		stream->send(message.c_str(), message.size());
		printf("sent - %s\n", message.c_str());
		
		char line[256];
		int len = stream->receive(line, sizeof(line));
		line[len] = NULL;
		printf("received - %s\n", line);
		delete stream;
	}

	std::cout<<"ok\n";
}