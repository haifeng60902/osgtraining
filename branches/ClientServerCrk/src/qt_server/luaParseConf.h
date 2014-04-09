#ifndef _LUA_PARSE_CONF_H_
#define _LUA_PARSE_CONF_H_

#include "Lua_hlp.h"
#include "binRigs.h"

class luaParseConf
{
public:
	luaParseConf();
	~luaParseConf();

	//parse lua config to settings
	void parse(const char* conf, binSetting* settings);

private:
	void parseWorkers(Lua::Config& config, tVecWorker *workers);
	void parseModes(Lua::Config& config, tVecMode *modes);
};

#endif	//_LUA_PARSE_CONF_H_