#include "DynamicLinesCallback.h"

#include "constant.h"

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectionVisitor>
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
	//при первом вызове добавить группу точек
	static bool bFirstTime = true;
	if ( bFirstTime )
	{
		osg::ref_ptr< osg::Group > group = GetLinesGroup( node );

		//найти массив вершин
		FindVertexArray( group.get() );

		//запоминаем узел
		m_pNode = node;

		//добавить к линиям точки
		group->addChild( m_PointsGroup.get() );

		bFirstTime = false;
	}

	//динамическое обновление положения линий
	DinamicUpdateLines();
}

void DynamicLinesCallback::DinamicUpdateLines()
{
	static int count = 0;

	if ( count > 60 * 10 )
	{
		for ( int i = 0 ; i < m_LinesVertexs->size() ; ++i )
		{
			( *m_LinesVertexs )[ i ] = osg::Vec3( GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) );
		}

		count = 0;
	}

	if ( count == 0 )
		//определение колизий
		ColisionDetection();

	++count;
}

//найти массив вершин
void DynamicLinesCallback::FindVertexArray( osg::ref_ptr< osg::Group > group )
{
	//динамическое обновление положения линий
	if ( group.valid() )
	{
		osg::ref_ptr< osg::Geode > geode = dynamic_cast< osg::Geode* >( group->getChild( 0 ) );

		if ( geode.valid() )
		{
			osg::ref_ptr< osg::Geometry > geom = dynamic_cast< osg::Geometry* >( geode->getDrawable( 0 ) );

			if ( geom.valid() )
			{
				// Create an array of four vertices.
				m_LinesVertexs = static_cast< osg::Vec3Array* >( geom->getVertexArray() );
			}
		}
	}
}

float DynamicLinesCallback::GetRand( float fScale )
{
	//получить случайное число
	return (float)rand() / (float)RAND_MAX * fScale - fScale * 0.5;
}

void DynamicLinesCallback::ColisionDetection()
{
	//определение колизий

	//вектор с результатом координат точек пересечения
	std::vector< osg::Vec3d > res;

	for ( int i = 0 ; i < m_LinesVertexs->size() / 2 ; ++i )
	{
		osg::ref_ptr< osgUtil::LineSegmentIntersector > intersector = 
			new osgUtil::LineSegmentIntersector( ( *m_LinesVertexs )[ 2 * i ] , 
			( *m_LinesVertexs )[ 2 * i + 1 ] );

		osgUtil::IntersectionVisitor iv( intersector.get() );

		m_pNode->accept( iv );

		if ( intersector->containsIntersections() )
		{
			osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();
			for(osgUtil::LineSegmentIntersector::Intersections::iterator itr = intersections.begin();
				itr != intersections.end();
				++itr)
			{
				const osgUtil::LineSegmentIntersector::Intersection& intersection = *itr;
				res.push_back( intersection.getWorldIntersectPoint() );
			}
		}
	}

	//заполнить узел новыми координатами точек
	FillPointsNode( res );
}

//найти группу линий
osg::ref_ptr< osg::Group > DynamicLinesCallback::GetLinesGroup( osg::Node* node )
{
	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group.valid() )
	{
		//получить количество потомков
		unsigned int num = group->getNumChildren();

		for ( unsigned int i = 0 ; i < num ; ++i )
		{
			osg::ref_ptr< osg::Group > grp = dynamic_cast< osg::Group* >( group->getChild( i ) );
			if ( ( grp.valid() ) && 
				( grp->getName() == std::string( "groupLines" ) ) )
			{
				return grp.get();
			}
		}
	}

	return group.get();
}

void DynamicLinesCallback::FillPointsNode( const std::vector< osg::Vec3d > &res )
{
	//заполнить узел новыми координатами точек
	m_V->clear();
	m_C->clear();

	m_V->resize( res.size() );
	m_C->resize( res.size() );

	for ( int i = 0 ; i < res.size() ; ++i )
	{
		( *m_V )[ i ] = res[ i ];//osg::Vec3( res[ i ][ 0 ] , GetRand( MAX_SIZE ) , GetRand( MAX_SIZE ) );
		( *m_C )[ i ] = osg::Vec4( GetRand( 1.0 ) + 0.5 , GetRand( 1.0 ) + 0.5 , GetRand( 1.0 ) + 0.5 , 1.0 );
	}

	m_DA->setCount( res.size() );
}