#include <iostream>
#include <string>

#include "Core/Lua/Lua_vm.h"
#include "ProxyLogic.h"

std::string sLocalAddress("127.0.0.1");
std::string sRemoteAddress("127.0.0.1");
int iLocalPort=9999;
int iRemotePort=8888;

int main(int argc, char **argv)
{
	//имя конфига
	for(int i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-config") == 0)
		{
			i++; if (i >= argc) break;
			Lua_vm lvm(argv[i]);
			sLocalAddress=lvm.get_string("local_address");
			sRemoteAddress=lvm.get_string("remote_address");
			iLocalPort=lvm.get_int("local_port");
			iRemotePort=lvm.get_int("remote_port");

			continue;
		}
	}

	ProxyLogic mProxyLogic;
	mProxyLogic.Init(sLocalAddress, sRemoteAddress, iLocalPort, iRemotePort);
	mProxyLogic.Process();
	
}