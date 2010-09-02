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

	//������� ������
	void CreateEffect( std::string sEffect );

private:
	//��������� ������ ���������
	void LoadEmitterArray( lua_State *L , tVecEmitter *pEmitters );

	//��������� ������ ���������� ��������
	void LoadEmitter( lua_State *L , binEmitter *pSubEmitter );

	//������� �������� ��������� ��������� 
	void LoadTexOffset( lua_State *L , float *pTexOffset );

	//����� �������
	int LoadFlags( lua_State *L );

	//�������� int �������� ����� �� �����
	int GetFlagByName(const char *name);

	//��������� �������
	void LoadCurves( lua_State *L , binEmitter *pSubEmitter );

	//�������� ��� �������� �� enum
	const char *GetEmitterParamName( enEmitter eEmitter );

	//�������� �������
	binEffect m_Effect;
};

#endif	//_PARTICLE_PLAYER_H_