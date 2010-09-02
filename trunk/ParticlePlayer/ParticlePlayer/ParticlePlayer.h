#ifndef _PARTICLE_PLAYER_H_
#define _PARTICLE_PLAYER_H_

#include "Singleton.h"
#include "Lua/Config.h"

#include <string>

#include "binEffect.h"

class ParticlePlayer : public Singleton< ParticlePlayer >
{
public:
	ParticlePlayer();
	~ParticlePlayer();

	//создать эффект
	void CreateEffect( std::string sEffect );

private:
	//загрузить массив эммитеров
	void LoadEmitterArray( lua_State *L , tVecEmitter *pEmitters );

	//загрузить данные очередного эммитера
	void LoadEmitter( lua_State *L , binEmitter *pSubEmitter );

	//считать смещения текстурых координат 
	void LoadTexOffset( lua_State *L , float *pTexOffset );

	//флаги эффекта
	int LoadFlags( lua_State *L );

	//получить int значения флага по имени
	int GetFlagByName(const char *name);

	//загрузить графики
	void LoadCurves( lua_State *L , binEmitter *pSubEmitter );

	//получить имя эмитрера по enum
	const char *GetEmitterParamName( enEmitter eEmitter );

	//описание эффекта
	binEffect m_Effect;
};

#endif	//_PARTICLE_PLAYER_H_