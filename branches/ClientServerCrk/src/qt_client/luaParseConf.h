#ifndef _LUA_PARSE_CONF_H_
#define _LUA_PARSE_CONF_H_

#include "Core/Lua/Lua_hlp.h"
#include "binClient.h"

class luaParseConf
{
public:
	luaParseConf();
	~luaParseConf();

	//parse lua config to settings
	void parse(const char* conf, binClient* client);

private:
	void extractCoins(Lua::Config* conf, tVecLuaCoin* pCoins);
	void extractMiners(Lua::Config* conf, tMapMiner* pMiners);
};

#endif	//_LUA_PARSE_CONF_H_