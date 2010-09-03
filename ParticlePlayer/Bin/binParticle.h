#ifndef _BIN_PARTICLE_H_ 
#define _BIN_PARTICLE_H_

#include <osg/Vec3f>
#include <osg/Vec4f>

#include <vector>

struct binParticle
{
	unsigned int m_uiID;	// particle id (flag 0x80000000 indicates particle is dead)

	osg::Vec3f m_v3Pos;     // position in local coords
	float m_fRoll;			// rotation (right now in screen coords)
	osg::Vec3f m_v3Speed;	// velocity in local coords
	osg::Vec3f m_v3Dir;		// direction of exhaust for super-emitters (may have other uses later)
	float m_fSpin;			// speed of roll
	float m_fBirth;        // time of birth in seconds
	float m_fLife;         // life length in seconds
	float m_fSize;         // size in meters
	float m_fWeight;       // how fast does it fall down
	osg::Vec4f m_v4Color;

	// parameters assigned to particle at birth
	osg::Vec3f m_v3InitSpeed;
	float m_fInitSpin;
	float m_fInitSize;
	float m_fInitWeight;
	osg::Vec4f m_v4InitColor;
	float m_TexOffset[ 4 ];
};

typedef std::vector< binParticle > tVecParticle;

#endif	//_BIN_PARTICLE_H_