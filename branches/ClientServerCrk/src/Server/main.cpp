#include <iostream>

#include "Core/Lua/Lua_vm.h"
#include "ServerLogic.h"
//#include "Tcp/TCPAcceptor.h"

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
//////////////////////////////////////////////////////////////////////////
	ServerLogic m_ServerLogic;

	m_ServerLogic.Init(iPort, sAddress);
	m_ServerLogic.Process();
	m_ServerLogic.Close();
}