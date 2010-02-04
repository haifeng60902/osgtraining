#include "LightPoint.h"

#include <osg/Geometry>

LightPoint::LightPoint()
{

}

LightPoint::~LightPoint()
{

}

void LightPoint::Init()
{
	//инициализация геометрического представления источника света
	m_Geode = new osg::Geode;

	//создать точку представляющую источник света
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -.1f, -.1f, -.1f, .1f, .1f, .1f );
	geom->setInitialBound( bbox );

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( 0.f, 0.f, 5.f ) );

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( GL_POINTS, 0, 1 ) );

	m_Geode->addDrawable( geom.get() );

	osg::StateSet* state = m_Geode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	osg::ref_ptr<osg::Point> pt = new osg::Point;
	pt->setSize( 10.f );
	state->setAttribute( pt.get() );
}