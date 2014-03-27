#include "luaParseConf.h"

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
	parseRigs(config, &settings->vRigs);
	parseModes(config, &settings->vModes);

	lua_close(l);
}

void luaParseConf::parseRigs(Lua::Config& config, tVecRig *rigs)
{
	if(config.open("rigs"))
	{
		config.iterate_begin();
		while(config.iterate_next())
		{
			binRig rig;
			rig.sRig=config.get("rig", std::string(""));
			rigs->push_back(rig);			
		}
		config.iterate_end();
		config.pop();
	}
}

void luaParseConf::parseModes(Lua::Config& config, tVecMode *modes)
{
	if(config.open("modes"))
	{
		config.iterate_begin();
		while(config.iterate_next())
		{
			binMode mode;
			mode.sCoin=config.get("coin", std::string(""));
			mode.sMiner=config.get("miner", std::string(""));
			mode.sIcon=config.get("icon", std::string(""));
			
			if(config.open("pools"))
			{
				config.iterate_begin();
				while(config.iterate_next())
				{
					std::string sPool;
					config.getStr(&sPool);
					mode.vPools.push_back(sPool);
				}

				config.iterate_end();
				config.pop();
			}

			modes->push_back(mode);			
		}
		config.iterate_end();
		config.pop();
	}
}