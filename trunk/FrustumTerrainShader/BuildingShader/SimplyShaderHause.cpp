#include "SimplyShaderHause.h"

#include "../PatchInfo.h"

#include <osg/Uniform>
#include <osg/BoundingBox>

SimplyShaderHause::SimplyShaderHause()
{
	m_rootNode = new osg::Group;

	//добавить модель из кэша
	m_rootNode->addChild( PatchInfo::Instance().GetModel( SCHOOL_106 ).get() );

	// определение ограничивающего объема, размер земли 256км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 256.0 * 1024.0 , 256.0 * 1024.0 , 64 );
	m_rootNode->setInitialBound( bbox );
}

void SimplyShaderHause::SetupUniform( const binHouse &_house )
{
	//настроить внутренний uniform
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	ss->addUniform( new osg::Uniform( "posOffset" , osg::Vec4( _house.m_dX , 
		_house.m_dY , 0.0f , 0.0f ) ) );
}