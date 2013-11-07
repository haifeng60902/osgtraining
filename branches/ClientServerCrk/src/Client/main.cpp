#include <iostream>

#include "Core/Lua/Lua_vm.h"
#include "ClientLogic.h"

std::string sAddress("127.0.0.1");
std::string sNode("local");
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
			sNode=lvm.get_string("node");
			iPort=lvm.get_int("port");
			continue;
		}
	}

//////////////////////////////////////////////////////////////////////////
	ClientLogic m_ClientLogic;

	bool bRes=m_ClientLogic.Init(iPort, sAddress, sNode);
	if (bRes)
	{
		m_ClientLogic.Process();
		m_ClientLogic.Close();
	}
}