#ifndef _DATA_VIS_PATCH_H_
#define _DATA_VIS_PATCH_H_

#include <osg/Geode>
#include <osg/Uniform>

#define DIST_SCALE 3.9f
#define GEOM_DIV 1

struct dataVisPatch
{
	dataVisPatch() : m_sOffset( "posOffset" )
		, m_sColorP( "colorP" )
		, m_sColorS( "colorS" )
		, m_sDist( "dist" )
	{};

	//геометри€ патча
	osg::ref_ptr< osg::Geode > m_Geode;

	//uniform дл€ динамического смещени€ геометрии патча
	osg::ref_ptr< osg::Uniform > m_unfOffset;

	//uniform дл€ задани€ основного цвета
	osg::ref_ptr< osg::Uniform > m_unfColorP;

	//uniform дл€ задани€ вспомогательного цвета
	osg::ref_ptr< osg::Uniform > m_unfColorS;

	//uniform дл€ задани€ рассто€ни€
	osg::ref_ptr< osg::Uniform > m_unfDist;

	//им€ переменной смещени€
	std::string m_sOffset;

	//им€ переменной основного цвета
	std::string m_sColorP;

	//им€ переменной вспомогательного цвета
	std::string m_sColorS;

	//им€ переменной рассто€ни€
	std::string m_sDist;
};

#endif	//_DATA_VIS_PATCH_H_