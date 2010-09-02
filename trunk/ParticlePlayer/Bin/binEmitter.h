#ifndef _BIN_EMITTER_H_
#define _BIN_EMITTER_H_

#include <vector>

struct binEmitter;

enum enEmitter
{
	epDirVariation = 0,     // no more than this angle from direction [0,Pi]
	epInnerExhaust,         // how particles fill insides of emission cone [0,1] (0 means particles emit only at the maximum variation angle)
	epVelocity,             // starting velocity in m/s
	epVelVariation,         // how much velicity varies [0,1]
	epParentVelocity,       // how much of emitter velocity particle gets [0,1]
	epLife,                 // life expectancy in seconds
	epLifeVariation,        // how much life can vary [0,1]
	epNumber,               // number of particles per second
	epSize,                 // size of particles
	epSizeVariation,        // how much size varies [0,1]
	epWeight,               // weight of particles
	epWeightVariation,      // [0,1]
	epSpin,                 // initial spin
	epSpinVariation,        // [0,1]
	epVisibility,           // alfa-blender [0,1]

	epVelocityOverLife,
	epSizeOverLife,
	epWeightOverLife,
	epSpinOverLife,

	epRedOverLife,
	epGreenOverLife,
	epBlueOverLife,
	epAlfaOverLife,

	epLast
};

//пара значений: время-значение
struct binCurve
{
	binCurve() : m_fTime( 0.0f )
		, m_fValue( 0.0f )
	{};

	float m_fTime;
	float m_fValue;
};

typedef std::vector< binCurve > tVecCurve;
typedef std::vector< tVecCurve > tVecVecCurve;
typedef std::vector< binEmitter > tVecEmitter;

struct binEmitter
{
	binEmitter()
	{
		m_vCurves.resize( epLast );
	};

	std::string m_sName;
	float m_TexOffset[ 4 ];
	int m_iFlags;
	tVecVecCurve m_vCurves;
	tVecEmitter m_vSubEmitters;
};

#endif	//_BIN_EMITTER_H_