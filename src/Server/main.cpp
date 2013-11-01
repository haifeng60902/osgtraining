#include <iostream>

//#include "lua/lua.hpp"
#include "core/Lua/Lua_vm.h"

int main()
{
	
	Lua_vm lvm("options.conf");

	std::cout << "vol is " << lvm.get_double("vol") << "\n";
	std::cout << "rho is " << lvm.get_int("rho") << "\n";
	std::cout << "method is " << lvm.get_string("method").c_str() << "\n";

	std::cout<<"ok\n";
}