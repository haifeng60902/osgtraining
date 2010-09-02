#ifndef ED_LUA_CONFIG_H
#define ED_LUA_CONFIG_H

#include "_config.h"

extern "C" {
#    include "lua.h"
#    include "lauxlib.h"
#    include "lualib.h"
}

#include <assert.h>
#include <string>

namespace Lua {

class StackCheck {
public:
#ifndef _DEBUG
		StackCheck(lua_State* s, int res=0) {}
#else
		StackCheck(lua_State* s, int res=0)	: L(s), top(lua_gettop(s) + res) {}
		~StackCheck() { assert( lua_gettop(L) == top ); }
private:
	lua_State* L;
	int top;
#endif
};

/*
	Usage:

	// reading
	Lua::Config conf = globalConfig;
	if( conf.open("my.config.table") ) {
		conf.get("int1", &i);
		conf.get("str2", &str);
		if( conf.open("sub_table") ) {
			conf.get("bool3", &b);
			conf.pop(); // pop "sub_table"
		}
		conf.get("sub_table.bool4", &b);
		conf.pop(); // pop "my.config.table"
	}

	// writing
	if( overwrite )
		conf.unset("my.conf.table");
	conf.create("my.conf.table");
		conf.set("bool1", b);
		conf.set("int2", i);
		conf.set("sub_table.bool3", b);
	conf.pop();

	// iteration
	conf.iterate_begin();
	while (conf.iterate_next()) {
		float v = 0;
		conf.get_key(v);
		break;
	}
	conf.iterate_end();
*/
class Config {
	lua_State* L;
	int top;
public:
		Config(lua_State* lua, int i=LUA_GLOBALSINDEX) : L(lua), top(lua_gettop(lua)) { lua_pushvalue(L, i); }
		// RAI - Resource Acquision is Initialization
		// NEVER EVER move destructor body into any kind of finish() function
		// Use scopes, Luke!!! {Lua::Config cfg(L); .... } <- here goes the destructor
		~Config() { lua_settop(L, top); }

	operator lua_State*() const { return L; }
	
// READING:
	// push table from path to stack
	// if result is false, NOTHING is pushed to the stack (not nil).
	ED_LUA_EXTERN bool open(const char* path);
    	ED_LUA_EXTERN bool open(int i);

	// open table without parsing
	ED_LUA_EXTERN bool open_raw(const char* name);


	// helpers
	template<typename T>
	bool get(const char* path, T* v) { get(path); return pop(v); }

	template<typename T>
	bool get(const char* path, T* v, const T& d) { get(path); if(pop(v)) return true; else {*v = d; return false;} }

	template<typename T>
	bool get(int key, T* v) { get(key); return pop(v); }

	template<typename T>
	bool get(int key, T* v, const T& d) { get(key); return pop(v) ? true : (*v = d), false; }

	// immediate mode
	template<typename T>
	T get(const char* path, const T& v) { T r(v); get(path); pop(&r); return r; }

	template<typename T>
	T get(int key, const T& v) { T r(v); get(key); pop(&r); return r; }


	// push value onto stack
	ED_LUA_EXTERN void get(const char* path);
	ED_LUA_EXTERN void get(int key);

	ED_LUA_EXTERN bool pop(bool*);
	ED_LUA_EXTERN bool pop(unsigned char*); // one char!
	ED_LUA_EXTERN bool pop(int*);
	ED_LUA_EXTERN bool pop(float*);
	ED_LUA_EXTERN bool pop(double*);
	ED_LUA_EXTERN bool pop(std::string*);
    ED_LUA_EXTERN bool pop(unsigned short*);
    ED_LUA_EXTERN bool pop(unsigned int*);
    ED_LUA_EXTERN bool pop(unsigned long*);

// WRITING:
	ED_LUA_EXTERN void unset(const char* path);

	// push table from path (and create if needed)
	ED_LUA_EXTERN void create(const char* path);
	ED_LUA_EXTERN void create(int key);

	ED_LUA_EXTERN void create_raw(const char* name);

	// helpers
	template<typename T>
	void set(const char* path, T val) { push(val); set(path); }

	template<typename T>
	void set(int key, T val) { push(val); set(key); }

	// set from the top of stack
	ED_LUA_EXTERN void set(const char* path);
	ED_LUA_EXTERN void set(int key);

	void push(bool v) { lua_pushboolean(L, v); }
	void push(int v) { lua_pushnumber(L, v); }
    void push(unsigned int v) { lua_pushnumber(L, v); }
	void push(double v) { lua_pushnumber(L, v); }
    void push(float v) { lua_pushnumber(L, v); }
	void push(const char* v) { lua_pushstring(L, v); }
	void push(const std::string& v) { lua_pushlstring(L, v.c_str(), v.length()); }
	void push(void * p) { lua_pushlightuserdata(L, p); }

// CALLING:
	bool call(const char* path, int nargs=0, int nresults=0)
	{
		lua_pushvalue(L, -1-nargs); // duplicate table
		get(path);
   		if (lua_isfunction(L, -1)) {
		    lua_remove(L, -2); // remove dupe
		    lua_insert(L, -1-nargs); // move func behind args
		    if(lua_pcall(L, nargs, nresults, 0)) {
               call_log(path,lua_tostring(L, -1));
			   lua_pop(L, 1);
			   return false;
		    }
		    return true;
        }
		lua_pop(L, 1);
		return true;
	}

	template<class A1, class A2, class A3, class A4>
	bool call(int nresults, const char* path, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
	{
		get(path);
		if (lua_isfunction(L, -1)) {
			push(a1);
			push(a2);
			push(a3);
			push(a4);
			if (lua_pcall(L, Var::Args<A1, A2, A3, A4>::Type::Length, nresults, 0)) {
                call_log(path,lua_tostring(L, -1));
				lua_pop(L, 1);
				return false;
			}
			return true;
		}
		lua_pop(L, 1);
		return false;
	}

	template<class A1>
	bool call(int nresults, const char* path, const A1& a1)
	{ return call(nresults, path, a1, Nil(), Nil(), Nil()); }

	template<class A1, class A2>
	bool call(int nresults, const char* path, const A1& a1, const A2& a2)
	{ return call(nresults, path, a1, a2, Nil(), Nil()); }

	template<class A1, class A2, class A3>
	bool call(int nresults, const char* path, const A1& a1, const A2& a2, const A3& a3)
	{ return call(nresults, path, a1, a2, a3, Nil()); }

// EVERYTHING:
	void pop(int n=1) { lua_pop(L, n); }

    ED_LUA_EXTERN bool dostring(const char* str);
	ED_LUA_EXTERN bool dofile(const char* file);

// ITERATION
	void iterate_begin() { lua_pushnil(L); lua_pushnil(L); }

	template<class T>
	void iterate_begin(const T& v) { push(v); lua_pushnil(L); }

	bool iterate_next()
	{
		lua_pop(L, 1);
		if (lua_next(L, -2))
			return true;
		lua_pushnil(L);
		lua_pushnil(L);
		return false;
	}
    // direct using of pop is impossible in current iteration routine 
    ED_LUA_EXTERN bool iterate_pop(bool*);
    ED_LUA_EXTERN bool iterate_pop(unsigned char*); // one char!
    ED_LUA_EXTERN bool iterate_pop(int*);
    ED_LUA_EXTERN bool iterate_pop(float*);
    ED_LUA_EXTERN bool iterate_pop(double*);
    ED_LUA_EXTERN bool iterate_pop(std::string*);

	void iterate_end() { lua_pop(L, 2); }

	// get current iteration key
	template<class T>
    bool get_key(T* v) { lua_pushvalue(L, -2); return pop(v); }

private: // NOCOPY
	Config(const Config&);
	void operator = (const Config&);

    ED_LUA_EXTERN void call_log(const char * path,const char * err) const;
};

}

#endif /* ED_LUA_CONFIG_H */
