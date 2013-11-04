#include <iostream>

#include "Core/Lua/Lua_vm.h"
#include "Tcp/TCPAcceptor.h"

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

	TCPAcceptor acceptor(iPort, sAddress.c_str());

	if (acceptor.start()==0)
	{
		TCPStream* stream = acceptor.accept();
		if (stream != NULL)
		{
			size_t len;
			char line[256];
			while ((len = stream->receive(line, sizeof(line))) > 0)
			{
				line[len] = NULL;
				std::cout<<"received - "<<line<<std::endl;
				stream->send(line, len);
			}

			delete stream;
		}
	}

	std::cout<<"ok\n";
}