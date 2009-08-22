#include "DynamicGroupUpdateCallback.h"

#include <iostream>

int iSlow = 0;

DynamicGroupUpdateCallback::DynamicGroupUpdateCallback( std::vector< osg::ref_ptr< osg::Geode > > &_vecGeode )
: m_vecGeode( &_vecGeode )
, m_iCount( -1 )
, m_iSign( 1 )
{

}

DynamicGroupUpdateCallback::~DynamicGroupUpdateCallback()
{

}

void DynamicGroupUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );
	
	if ( ( group ) )//&& !( iSlow % 20 ) )
	{
		if ( m_iCount < 0 )
			m_iCount = group->getNumChildren();
	
		if ( ( m_iCount == 1) || ( m_iCount > 15 )) 
			m_iSign *= -1;

		m_iCount += m_iSign;

		std::cout << m_iCount << " ";

		group->removeChildren( 0 , m_vecGeode->size() );

		for ( int i = 0 ; i < m_iCount ; ++i )
		{
			group->addChild( m_vecGeode->at( i ).get() );
		}
	}

	++iSlow;
}