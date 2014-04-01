#ifndef _LUA_HLP_H_
#define _LUA_HLP_H_

#include <string>
#include "lua/lua.hpp"

namespace Lua
{
	class Config
	{
	public:
		Config(lua_State* lua, int i=LUA_GLOBALSINDEX):L(lua), top(lua_gettop(lua)){lua_pushvalue(L, i);};

		~Config() { lua_settop(L, top); }

		operator lua_State*() const { return L; }

		bool dofile(const char* file);

		bool open(const char* path);
		bool open(int i);
		void iterate_begin() { lua_pushnil(L); lua_pushnil(L); }

		bool iterate_next()
		{
			lua_pop(L, 1);
			if (lua_next(L, -2))
				return true;
			lua_pushnil(L);
			lua_pushnil(L);
			return false;
		}

		void iterate_end() { lua_pop(L, 2); }
		void pop(int n=1) { lua_pop(L, n); }

		// immediate mode
		template<typename T>
		T get(const char* path, const T& v) { T r(v); get(path); pop(&r); return r; }

		template<typename T>
		bool get(int key, T* v) { get(key); return pop(v); }

		bool getStr(std::string* v);

		bool pop(std::string*);
		bool pop(bool*);
		bool pop(int*);
		bool pop(float*);
		bool pop(double*);

	private:
		// push value onto stack
		void get(const char* path);
		void get(int key);

		lua_State* L;
		int top;
	};

}//namespace Lua
#endif //_LUA_HLP_H_