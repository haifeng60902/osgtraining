#include "Lua_hlp.h"
#include <iostream>

static int push_path(lua_State* L, const char* path, bool(*open)(lua_State*))
{
	const char* dot = strchr(path, '.');
	if( !dot ) {
		lua_pushstring(L, path);
		return 1;
	}
	lua_pushvalue(L, -1); //duplicate table

	const char* head = path;
	const char* tail = dot;
	do
	{
		lua_pushlstring(L, head, tail-head);
		if( !(*open)(L) ) {
			lua_pop(L, 1);
			return 0;
		}
		lua_remove(L, -2);
		head = tail + 1;
	} while( (tail = strchr(head, '.')) );
	lua_pushstring(L, head);
	return 2;
}

static int push_path(lua_State* L, int path, bool(*open)(lua_State*))
{
	lua_pushinteger(L, path);
	return 1;
}

static bool open_table(lua_State* L)
{
	if (!lua_istable(L, -2)) {
		lua_pop(L, 1);
		return false;
	}
	lua_gettable(L, -2);
	if( lua_isnil(L, -1) ) {
		lua_pop(L, 1);
		return false;
	}
	return true;
}

bool Lua::Config::dofile(const char* file)
{
	if (luaL_dofile(L, file))
	{
		std::cout<<"Lua error "<<lua_tostring(L, -1)<<" in "<<file<<std::endl;
		lua_pop(L, 1);
		return false;
	}
	return true;
}

//READING
void Lua::Config::get(const char* path)
{
	int n = push_path(L, path, open_table);
	if( n == 0 )
		lua_pushnil(L);
	else {
		lua_gettable(L, -2);
		if( n > 1 )
			lua_remove(L, -2);
	}
}

void Lua::Config::get(int key)
{
	lua_pushnumber(L, key);
	lua_gettable(L, -2);
}

// push table from path
bool Lua::Config::open(const char* path)
{
	get(path);
	if( !lua_istable(L, -1) )
	{
		lua_pop(L, 1);
		return false;
	}
	return true;
}

bool Lua::Config::open(int i)
{
	get(i);
	if( !lua_istable(L, -1) )
	{
		lua_pop(L, 1);
		return false;
	}
	return true;
}

bool Lua::Config::pop(std::string* v)
{
#if 1
	// string type only
	bool valid = lua_isstring(L, -1) ? true : false;
	if( valid )
		*v = lua_tostring(L, -1);
	lua_pop(L, 1);
	return valid;
#else
	// convert everything to string
	const char* res = lua_tostring(L, -1);
	if (res)
		*v = res;
	lua_pop(L, 1);
	return res;
#endif
}

bool Lua::Config::getStr(std::string* v)
{
	// string type only
	bool valid = lua_isstring(L, -1) ? true : false;
	if( valid )
		*v = lua_tostring(L, -1);
	return valid;
}

// wrappers
template<typename T> static inline
	bool popnumber(Lua::Config& conf, T* res)
{
	bool valid = lua_isnumber(conf, -1) ? true : false;
	if( valid )
		*res = (T)lua_tonumber(conf, -1);
	conf.pop(1);
	return valid;
}


bool Lua::Config::pop(int* v)
{
	return popnumber(*this, v);
}

bool Lua::Config::pop(float* v)
{
	return popnumber(*this, v);
}

bool Lua::Config::pop(double* v)
{
	return popnumber(*this, v);
}
