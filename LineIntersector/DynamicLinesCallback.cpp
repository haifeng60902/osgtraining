#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>

#include <iostream>

DynamicLinesCallback::DynamicLinesCallback()
{

}

DynamicLinesCallback::~DynamicLinesCallback()
{

}

void DynamicLinesCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group.valid() )
	{
		osg::ref_ptr< osg::Geode > geode = dynamic_cast< osg::Geode* >( group->getChild( 0 ) );

		if ( geode.valid() )
		{
			osg::ref_ptr< osg::Geometry > geom = dynamic_cast< osg::Geometry* >( geode->getDrawable( 0 ) );
			
			if ( geom.valid() )
			{
				 // Create an array of four vertices.
				 osg::Vec3Array* v = static_cast< osg::Vec3Array* >( geom->getVertexArray() );

				 for ( int i = 0 ; i < v->size() ; ++i )
				 {
						 ( *v )[ i ] = osg::Vec3( GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) );
				 }
			}
		}
	}
}

float DynamicLinesCallback::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale;
}