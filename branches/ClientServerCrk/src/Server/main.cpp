#include <iostream>

#include "core/Lua/Lua_vm.h"
#include "tcp/tcpacceptor.h"

int main()
{
	
	Lua_vm lvm("options.conf");

	std::cout << "vol is " << lvm.get_double("vol") << "\n";
	std::cout << "rho is " << lvm.get_int("rho") << "\n";
	std::cout << "method is " << lvm.get_string("method").c_str() << "\n";

	TCPAcceptor acceptor(9999,"127.0.0.1");

	std::cout<<"ok\n";
}