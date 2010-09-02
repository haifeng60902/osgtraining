#include "Config.h"
#include <string.h>

#define ED_LOG_MODULE "Lua::Config"

#if 0
#include <windows.h>

static void lua_Dump(lua_State* L)
{
	char dump[256];
	int left = sizeof(dump);
	int pos = 0;
	int count = lua_gettop(L);
	for(int i=count; i>0; --i)
	{
		int done = _snprintf(dump+pos, left, "%d: %s = (%08x) %s\n",
			i, lua_typename(L, lua_type(L,i)), lua_topointer(L, i), lua_tostring(L, i));
		pos += done;
		left -= done;
	}
	OutputDebugString("--- Lua::Config stack dump --------\n");
	OutputDebugString(dump);
	OutputDebugString("-----------------------------------\n");
}
#endif

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

static bool create_table(lua_State* L)
{
	Lua::StackCheck check(L);

	lua_pushvalue(L, -1);
	lua_gettable(L, -3);
	if( lua_isnil(L, -1) ) {
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L, -1); // duplicate new table
		lua_insert(L, -3); // move copy deeper
		lua_settable(L, -4);
	} else
		lua_remove(L, -2); // drop string copy
	return true;
}

static int push_path(lua_State* L, const char* path, bool(*open)(lua_State*))
{
	assert( lua_istable(L, -1) );
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
		assert( lua_istable(L, -1) );
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
    assert( lua_istable(L, -1) );
    lua_pushinteger(L, path);
    return 1;
}

//READING
void Lua::Config::get(const char* path)
{
	Lua::StackCheck check(L, 1);

	assert( lua_istable(L, -1) );

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
	Lua::StackCheck check(L, 1);
	assert( lua_istable(L, -1) );

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

bool Lua::Config::open_raw(const char* name)
{
	assert( lua_istable(L, -1) );
	lua_pushstring(L, name);
	lua_gettable(L, -2);
	if( !lua_istable(L, -1) )
	{
		lua_pop(L, 1);
		return false;
	}
	return true;
}


//WRITING
// push table from path (and create if needed)
void Lua::Config::create(const char* path)
{
	Lua::StackCheck check(L, 1);

	int n = push_path(L, path, create_table);

	assert( (n == 1 || n == 2) );
	assert( lua_istable(L, -2) );

	create_table(L);

	if( n == 2 )
		lua_remove(L, -2); // table from path
}

void Lua::Config::create(int key)
{
	Lua::StackCheck check(L, 1);

	lua_pushnumber(L, key);
	create_table(L);
}

void Lua::Config::create_raw(const char* name)
{
	Lua::StackCheck check(L, 1);

	lua_pushstring(L, name);
	create_table(L);
}

void Lua::Config::set(const char* path)
{
	Lua::StackCheck check(L, -1);

	lua_insert(L, -2);
	int n = push_path(L, path, create_table);

	assert( (n == 1 || n == 2) );
	assert( lua_istable(L, -2) );

	lua_pushvalue(L, -2-n);
	lua_settable(L, -3);
	if( n == 2 )
		lua_pop(L, 1);
	lua_remove(L, -2);
}

void Lua::Config::set(int path)
{
    Lua::StackCheck check(L, -1);

    lua_insert(L, -2);
    int n = push_path(L, path, create_table);

    assert( (n == 1 || n == 2) );
    assert( lua_istable(L, -2) );

    lua_pushvalue(L, -2-n);
    lua_settable(L, -3);
    if( n == 2 )
        lua_pop(L, 1);
    lua_remove(L, -2);
}

void Lua::Config::unset(const char* path)
{
	Lua::StackCheck check(L);

	int n = push_path(L, path, open_table);
	if( n ) {
		lua_pushnil(L);
		lua_settable(L, -3);
	}
	if( n == 2 )
		lua_pop(L, 1); // drop table
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

template<typename T> static inline
bool iterate_popnumber(Lua::Config& conf, T* res)
{
    bool valid = lua_isnumber(conf, -1) ? true : false;
    if( valid )
        *res = (T)lua_tonumber(conf, -1);
    return valid;
}

bool Lua::Config::pop(unsigned char* v)
{
	return popnumber(*this, v);
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

bool Lua::Config::pop(unsigned short* v)
{
    return popnumber(*this, v);
}

bool Lua::Config::pop(unsigned int* v)
{
    return popnumber(*this, v);
}

bool Lua::Config::pop(unsigned long* v)
{
    return popnumber(*this, v);
}

bool Lua::Config::pop(bool* v)
{
	bool valid = lua_isboolean(L, -1);
	if( valid )
		*v = lua_toboolean(L, -1) ? true : false;
	lua_pop(L, 1);
	return valid;
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


bool  Lua::Config::iterate_pop(bool* v)
{
    bool valid = lua_isboolean(L, -1);
    if( valid )
        *v = lua_toboolean(L, -1) ? true : false;
    return valid;
}

bool  Lua::Config::iterate_pop(unsigned char* v) // one char!
{
    return iterate_popnumber(*this, v);
}

bool  Lua::Config::iterate_pop(int* v)
{
    return iterate_popnumber(*this, v);
}

bool  Lua::Config::iterate_pop(float* v)
{
    return iterate_popnumber(*this, v);
}

bool  Lua::Config::iterate_pop(double* v)
{
    return iterate_popnumber(*this, v);
}

bool  Lua::Config::iterate_pop(std::string* v)
{
    bool valid = lua_isstring(L, -1) ? true : false;
    if( valid )
        *v = lua_tostring(L, -1);
    return valid;
}

void  Lua::Config::call_log(const char * path,const char * err) const
{ 
    //ED_ERROR("Call error %s:%s.",path,err);
    assert(!"Lua::Config::call");
}

bool Lua::Config::dostring(const char* str)
{
	if (luaL_dostring(L, str))
	{
		//ED_ERROR("Can't load \"%s\": %s.", str, lua_tostring(L, -1));
	    assert(!"Lua::Config::dostring");
		lua_pop(L, 1);
		return false;
	}
	return true;
}

bool Lua::Config::dofile(const char* file)
{
	if (luaL_dofile(L, file))
	{
		//ED_ERROR("Can't load %s: %s.", file, lua_tostring(L, -1));
	    //assert(!"Lua::Config::dofile");
		lua_pop(L, 1);
		return false;
	}
	return true;
}
