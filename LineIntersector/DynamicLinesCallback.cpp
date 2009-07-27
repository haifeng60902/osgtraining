#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/LineSegmentIntersector>
#include <osg/Point>

#include <iostream>

DynamicLinesCallback::DynamicLinesCallback()
{
	//инициализация узла, содержащего точки
	InitPointsNode();
}

DynamicLinesCallback::~DynamicLinesCallback()
{

}

void DynamicLinesCallback::InitPointsNode()
{
	//инициализация узла, содержащего точки
	m_PointsGroup = new osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	m_V = new osg::Vec3Array;
	geom->setVertexArray( m_V.get() );

	// Create an array of four vertices.
	m_C = new osg::Vec4Array;
	geom->setColorArray( m_C.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );

	m_DA = new osg::DrawArrays( osg::PrimitiveSet::POINTS, 0, 0 );

	geom->addPrimitiveSet( m_DA.get() );

	geom->setUseDisplayList( false );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	m_PointsGroup->addChild( geode.get() );

	//динамически меняемый узел
	m_PointsGroup->setDataVariance( osg::Object::DYNAMIC );

	osg::StateSet* state = m_PointsGroup->getOrCreateStateSet();

	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	osg::ref_ptr< osg::Point > pt = new osg::Point;
	pt->setSize( 10.f );
	state->setAttribute( pt.get() );
}

void DynamicLinesCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//динамическое обновление положения линий
	DinamicUpdateLines( node );

	osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = 
		new osgUtil::LineSegmentIntersector( osg::Vec3(-100,-100,-100) , osg::Vec3(100,100,100) );

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

	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group.valid() )
	{
		//при первом вызове добавить группу точек
		static bool bFirstTime = true;
		if ( bFirstTime )
		{
			group->addChild( m_PointsGroup.get() );
			bFirstTime = false;
		}

		osg::ref_ptr< osg::Geode > geode = dynamic_cast< osg::Geode* >( group->getChild( 0 ) );

		if ( geode.valid() )
		{
			osg::ref_ptr< osg::Geometry > geom = dynamic_cast< osg::Geometry* >( geode->getDrawable( 0 ) );

			if ( geom.valid() )
			{
				// Create an array of four vertices.
				osg::Vec3Array* v = static_cast< osg::Vec3Array* >( geom->getVertexArray() );

				if ( count > 60 * 5 )
				{
					for ( int i = 0 ; i < v->size() ; ++i )
					{
						( *v )[ i ] = osg::Vec3( GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) );
					}

					count = 0;
				}

				//определение колизий
				ColisionDetection( v , node );
			}
		}
	}


	++count;
}

float DynamicLinesCallback::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}

void DynamicLinesCallback::ColisionDetection( osg::Vec3Array* v , osg::Node* node )
{
	//определение колизий

	for ( int i = 0 ; i < v->size() / 2 ; ++i )
	{
		osg::ref_ptr< osgUtil::LineSegmentIntersector > intersector = 
			new osgUtil::LineSegmentIntersector( ( *v )[ 2 * i ] , ( *v )[ 2 * i + 1 ] );

		osgUtil::IntersectionVisitor iv( intersector.get() );

		node->accept( iv );

		if (intersector->containsIntersections())
		{
			std::cout << "yes ";
		}
	}

//////////////////////////////////////////////////////////////////////////
	/*
	m_V->clear();
	m_C->clear();

	m_V->resize( v->size() / 2 );
	m_C->resize( v->size() / 2 );

	for ( int i = 0 ; i < v->size() / 2 ; ++i )
	{
		( *m_V )[ i ] = osg::Vec3( GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) );
		( *m_C )[ i ] = osg::Vec4( GetRand( 1.0 ) + 0.5 , GetRand( 1.0 ) + 0.5 , GetRand( 1.0 ) + 0.5 , 1.0 );
	}

	m_DA->setCount( v->size() / 2 );
	*/
}
