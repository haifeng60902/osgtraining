#include "luaParseConf.h"

#include "Lua_hlp.h"

luaParseConf::luaParseConf()
{

}

luaParseConf::~luaParseConf()
{

}

void luaParseConf::parse(const char* conf, binSetting* settings)
{
	//parse lua config to settings
	lua_State* l=lua_open();
	luaL_openlibs(l);

	Lua::Config config(l);

	if (!config.dofile(conf))
		return;

	settings->iColumn = config.get("column", 0);
	if(config.open("rigs"))
	{
		config.iterate_begin();
		while(config.iterate_next())
		{
			binRig rig;
			rig.sRig=config.get("rig", std::string(""));
			settings->vRigs.push_back(rig);			
		}
		config.iterate_end();
		config.pop();
	}

	lua_close(l);
}