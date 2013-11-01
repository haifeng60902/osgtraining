#include <iostream>

#include "lua/lua.hpp"


int main()
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	int s = luaL_loadfile(L, "options.conf");

	if ( s==0 ) {
		// execute Lua program
		//s = lua_pcall(L, 0, LUA_MULTRET, 0);

		lua_getglobal(L,"sdf");
	}

	lua_close(L);

	std::cout<<"ok\n";
}