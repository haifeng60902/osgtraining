#ifndef _LUA_VM_H_
#define _LUA_VM_H_

#include "lua/lua.hpp"

class Lua_vm 
{
private:
	lua_State *L;
public:
	double get_double(const char *var_name) {
		lua_getglobal(L,var_name);
		if (!lua_isnumber(L,-1)) {
			std::cout << "error: " << var_name << " is of a wrong type\n";
		}
		return (double)lua_tonumber(L,-1);
		lua_pop(L,1);
	}
	int get_int(const char *var_name) {
		lua_getglobal(L,var_name);
		if (!lua_isnumber(L,-1)) {
			std::cout << "error: " << var_name << " is of a wrong type\n";
		}
		return (int)lua_tonumber(L,-1);
		lua_pop(L,1);
	}
	std::string get_string(const char *var_name) {
		lua_getglobal(L,var_name);
		if (!lua_isstring(L,-1)) {
			std::cout << "error: " << var_name << " is of a wrong type\n";
		}
		return std::string(lua_tostring(L,-1));
		lua_pop(L,1);
	}
	Lua_vm(const char *lua_config_filename) {
		L = lua_open();
		if (luaL_loadfile(L, lua_config_filename) || lua_pcall(L, 0,0,0)) {
			std::cout << "error: " << lua_tostring(L,-1) << "\n";
		}
		lua_pushnil(L);
	}
	~Lua_vm() {
		lua_close(L);
	}
};

#endif	//_LUA_VM_H_