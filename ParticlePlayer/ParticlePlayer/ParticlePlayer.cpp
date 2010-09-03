#include "ParticlePlayer.h"

#include <iostream>

const char *pFlagNames[] = {
	"Sort",
	"Intense",
	"AlignToMotion",
	"LightSource",
	0
};

const char *pParamNames[] = {
	"DirVariation",         // no more than this angle from direction [0,Pi]
	"InnerExhaust",         // how particles fill insides of emission cone [0,1] (0 means particles emit only at the maximum variation angle)
	"Velocity",             // starting velocity in m/s
	"VelVariation",         // how much velicity varies [0,1]
	"ParentVelocity",       // how much of emitter velocity particle gets [0,1]
	"Life",                 // life expectancy in seconds
	"LifeVariation",        // how much life can vary [0,1]
	"Number",               // number of particles per second
	"Size",                 // size of particles
	"SizeVariation",        // how much size varies [0,1]
	"Weight",               // weight of particles
	"WeightVariation",      // [0,1]
	"Spin",                 // initial spin
	"SpinVariation",        // [0,1]
	"Visibility",           // alfa-blender [0,1]

	"VelocityOverLife",
	"SizeOverLife",
	"WeightOverLife",
	"SpinOverLife",
	"RedOverLife",
	"GreenOverLife",
	"BlueOverLife",
	"AlfaOverLife",

	0
};

ParticlePlayer::ParticlePlayer()
{

}

ParticlePlayer::~ParticlePlayer()
{

}

void ParticlePlayer::CreateEffect( std::string sEffect )
{
	//создать эффект
	lua_State *L = lua_open();
	{
		Lua::Config config( L );
		if( !config.dofile( sEffect.c_str() ) )
		{
			std::cout << "error\n";
		}
		else
		{
			if( config.open( "Emitters" ) )
			{
				//загрузить массив эммитеров
				LoadEmitterArray( L , &m_Effect.m_vEmitters );
				config.pop();
			}
		}
	}

	lua_close(L);
}

void ParticlePlayer::LoadEmitterArray( lua_State *L , tVecEmitter *pEmitters )
{
	//загрузить массив эммитеров
	Lua::Config config( L , -1 );
	for( int j = 1 ; config.open( j ) ; ++j )
	{
		bool bDisable = false;
		config.get( "disable" , &bDisable );
		if( !bDisable )
		{
			binEmitter bSubEmitter;
			LoadEmitter( L , &bSubEmitter );

			pEmitters->push_back( bSubEmitter );
		}
		config.pop();
	}
}

void ParticlePlayer::LoadEmitter( lua_State *L , binEmitter *pSubEmitter )
{
	//загрузить данные очередного эммитера
	Lua::Config config( L , -1 );

	//имя эммитера
	config.get( "Name" , &pSubEmitter->m_sName );

	//считать смещения текстурых координат 
	LoadTexOffset( L , pSubEmitter->m_TexOffset );

	//флаги эффекта
	pSubEmitter->m_iFlags = LoadFlags( L );

	LoadCurves( L , pSubEmitter );

	if( config.open( "SubEmitters" ) )
	{
		//загрузить массив эммитеров
		LoadEmitterArray( L , &pSubEmitter->m_vSubEmitters );
		config.pop();
	}
}

void ParticlePlayer::LoadTexOffset( lua_State *L , float *pTexOffset )
{
	//считать смещения текстурых координат 
	Lua::Config config( L , -1 );

	if( !config.open( "TexOffset" ) )
		return;

	float fOffset;
	for( int i = 1 ; config.get( i , &fOffset ) ; ++i )
	{
		if ( i > 4 )
			break;

		pTexOffset[ i - 1 ] = fOffset;
	}

	config.pop();
}

int ParticlePlayer::LoadFlags( lua_State *L )
{
	//флаги эффекта
	Lua::Config config( L , -1 );

	int iFlags = 0;
	if( !config.open( "Flags" ) )
		return 0;

	std::string sFName;
	for(int i = 1 ; config.get( i , &sFName ); ++i )
		iFlags |= GetFlagByName( sFName.c_str() );

	config.pop();
	return iFlags;
}

int ParticlePlayer::GetFlagByName(const char *name)
{
	//получить int значения флага по имени
	for( int i = 0 ; pFlagNames[ i ] ; ++i )
	{
		if( !strcmp( name, pFlagNames[i] ) )
			return 1 << i;
	}
	return 0;
}

void ParticlePlayer::LoadCurves( lua_State *L , binEmitter *pSubEmitter )
{
	//загрузить графики
	Lua::Config config( L , -1 );
	for( int i = 0 ; i < epLast ; ++i )
	{
		tVecCurve &vCurve = pSubEmitter->m_vCurves[ i ];

		const char *pName = GetEmitterParamName( ( enEmitter )i );
		
		if( !config.open( pName ) )
			continue;

		for( int j = 1; config.open(j) ; ++j)
		{
			binCurve key;
			config.get( 1 , &key.m_fTime );
			config.get( 2 , &key.m_fValue );
			vCurve.push_back( key );
			config.pop();
		}
		config.pop();
	}
}

const char *ParticlePlayer::GetEmitterParamName( enEmitter eEmitter )
{
	//получить имя эмитрера по enum
	if( eEmitter < epLast)
		return pParamNames[ eEmitter ];
	return 0;
}