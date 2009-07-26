#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/LineSegmentIntersector>

#include <iostream>

DynamicLinesCallback::DynamicLinesCallback()
{

}

DynamicLinesCallback::~DynamicLinesCallback()
{

}

void DynamicLinesCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//динамическое обновление положения линий
	DinamicUpdateLines( node );

	osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = 
		new osgUtil::LineSegmentIntersector( osg::Vec3(0,0,0) , osg::Vec3(0,0,1) );

	osgUtil::IntersectionVisitor iv( intersector.get() );

	node->accept( iv );

	if (intersector->containsIntersections())
	{
		std::cout << "yes ";
	}
}

void DynamicLinesCallback::DinamicUpdateLines( osg::Node* node )
{
	//динамическое обновление положения линий
	static int count = 0;

	if ( count > 60 * 5 )
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
		count = 0;
	}

	++count;
}

float DynamicLinesCallback::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}