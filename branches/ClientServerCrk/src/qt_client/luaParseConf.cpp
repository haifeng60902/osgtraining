#include "luaParseConf.h"

luaParseConf::luaParseConf()
{

}

luaParseConf::~luaParseConf()
{

}
void luaParseConf::parse(const char* conf, binClient* client)
{
	//parse lua config to settings
	lua_State* l=lua_open();
	luaL_openlibs(l);

	Lua::Config config(l);

	if (!config.dofile(conf))
		return;
	
	client->bShowSysTray = config.get("systray", 1);
	client->sUser = config.get("user", std::string(""));
	client->sPass = config.get("pass", std::string(""));
	
	extractCoins(&config, &client->vCoins);
	extractMiners(&config, &client->mMiners);

	lua_close(l);
}

void luaParseConf::extractCoins(Lua::Config* conf, tVecCoin* pCoins)
{
	if (conf->open("coins"))
	{
		conf->iterate_begin();
		while(conf->iterate_next())
		{
			binCoin coin;
			coin.sCoin = conf->get("coin", std::string(""));
			coin.sMiner = conf->get("miner", std::string(""));
			coin.sIcon = conf->get("icon", std::string(""));

			if(conf->open("pools"))
			{
				conf->iterate_begin();
				while(conf->iterate_next())
				{
					std::string sPool;
					conf->getStr(&sPool);
					coin.vPools.push_back(sPool);
				}

				conf->iterate_end();
				conf->pop();
			}

			pCoins->push_back(coin);			
		}
		conf->iterate_end();
		conf->pop();
	}
}

void luaParseConf::extractMiners(Lua::Config* conf, tMapMiner* pMiners)
{
	if (conf->open("miners"))
	{
		conf->iterate_begin();
		while(conf->iterate_next())
		{
			std::string sMiner;
			binParam param;
			sMiner = conf->get("miner", std::string(""));
			param.sPath = conf->get("path", std::string(""));
			param.sParam = conf->get("param", std::string(""));

			(*pMiners)[sMiner]=param;
		}
		conf->iterate_end();
		conf->pop();
	}
}