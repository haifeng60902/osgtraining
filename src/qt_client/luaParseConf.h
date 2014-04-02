#ifndef _LUA_PARSE_CONF_H_
#define _LUA_PARSE_CONF_H_

#include "binClient.h"

class luaParseConf
{
public:
	luaParseConf();
	~luaParseConf();

	//parse lua config to settings
	void parse(const char* conf, binClient* client);
};

#endif	//_LUA_PARSE_CONF_H_