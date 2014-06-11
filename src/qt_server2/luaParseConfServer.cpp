#include "luaParseConfServer.h"

luaParseConfServer::luaParseConfServer()
{

}

luaParseConfServer::~luaParseConfServer()
{

}

void luaParseConfServer::parse(const char* conf, binSetting* settings)
{
	//parse lua config to settings
	lua_State* l=lua_open();
	luaL_openlibs(l);

	Lua::Config config(l);

	if (!config.dofile(conf))
		return;

	settings->iColumn = config.get("column", 0);
	settings->iPort = config.get("port", 9800);
	settings->iWait = config.get("wait", 30);
	parseWorkers(config, &settings->vWorker);
	parseModes(config, &settings->vModes);

	lua_close(l);
}

void luaParseConfServer::parseWorkers(Lua::Config& config, tVecWorker *workers)
{
	if(config.open("workers"))
	{
		config.iterate_begin();
		while(config.iterate_next())
		{
			binWorker worker;
			worker.sWorker=config.get("worker", std::string(""));
			workers->push_back(worker);			
		}
		config.iterate_end();
		config.pop();
	}
}

void luaParseConfServer::parseModes(Lua::Config& config, tVecMode *modes)
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