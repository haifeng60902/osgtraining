#ifndef _LUA_PARSE_CONF_SERVER_H_
#define _LUA_PARSE_CONF_SERVER_H_

#include "core/Lua/Lua_hlp.h"
#include "binRigs.h"

class luaParseConfServer
{
public:
	luaParseConfServer();
	~luaParseConfServer();

	//parse lua config to settings
	void parse(const char* conf, binSetting* settings);

private:
	void parseWorkers(Lua::Config& config, tVecWorker *workers);
	void parseModes(Lua::Config& config, tVecMode *modes);
};

#endif	//_LUA_PARSE_CONF_SERVER_H_