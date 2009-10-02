#include "osgIsectorHAT.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectionVisitor>


osgIsectorHAT::osgIsectorHAT() : m_bEnable( true )
{
	//создание osg::Switch
	m_Switch = new osg::Switch;

	//создание линии для отладочных целей
	InitLine();

	//динамически меняемый узел
	m_Switch->setDataVariance( osg::Object::DYNAMIC );
}

void osgIsectorHAT::setPositionReference( osg::ref_ptr<osg::MatrixTransform> _mt )
{
	//внешняя стратегия перемещения
	_mt->addChild( m_Switch.get() );
}

void osgIsectorHAT::setRenderEnable( bool _bEnable )
{
	//включить режим отображения линии isector'a
	m_Switch->setValue( 0 , _bEnable );
	m_bRender = _bEnable;
}

void osgIsectorHAT::setSegmentZExtent( float _dMinZ , float _dMaxZ )
{
	//размер isector'a
	( *m_v3V )[ 0 ] = osg::Vec3( 0.0f , 0.0f , _dMinZ );
	( *m_v3V )[ 1 ] = osg::Vec3( 0.0f , 0.0f , _dMaxZ );
}

float osgIsectorHAT::GetHAT()
{
	//узнать высоту пересечения

	//вектор с результатом координат точек пересечения
	std::vector< osg::Vec3d > res;

	for ( int i = 0 ; i < m_v3V->size() / 2 ; ++i )
	{
		osg::ref_ptr< osgUtil::LineSegmentIntersector > intersector = 
			new osgUtil::LineSegmentIntersector( ( *m_v3V )[ 2 * i ] , 
			( *m_v3V )[ 2 * i + 1 ] );

		osgUtil::IntersectionVisitor iv( intersector.get() );

		m_SceneRoot->accept( iv );

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

	return res.size();
}

void osgIsectorHAT::InitLine()
{
	//создание линии для отладочных целей

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	m_v3V = new osg::Vec3Array;
	geom->setVertexArray( m_v3V.get() );

	// Create an array of colors.
	m_v4C = new osg::Vec4Array;
	geom->setColorArray( m_v4C.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE );

	for ( int i = 0 ; i < 1 ; ++i )
	{
		//добавляем пару вершин со случайными координатами
		m_v3V->push_back( osg::Vec3( 0.0f , 0.0f , -1.0f ) );
		m_v3V->push_back( osg::Vec3( 0.0f , 0.0f , 1.0f ) );

		//цвет общий на примитив
		m_v4C->push_back( osg::Vec4( 0.0, 1.0, 0.0 , 1.0 ) );
	}

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, 0, 2 ) );

	geom->setUseDisplayList( false );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	//добавить линию в osg::Swith
	m_Switch->addChild( geode.get() );
}