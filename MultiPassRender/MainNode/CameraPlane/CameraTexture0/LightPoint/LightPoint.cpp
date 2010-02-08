#include "LightPoint.h"

#include "UpdClbkLightPoint.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Point>

LightPoint::LightPoint()
{

}

LightPoint::~LightPoint()
{

}

void LightPoint::Init()
{
	//инициализация геометрического представления источника света
	osg::ref_ptr< osg::Geode > mGeode = new osg::Geode;

	//создать точку представляющую источник света
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -.1f, -.1f, -.1f, .1f, .1f, .1f );
	geom->setInitialBound( bbox );

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( 0.f, 0.f, 0.f ) );

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( GL_POINTS, 0, 1 ) );

	mGeode->addDrawable( geom.get() );

	osg::StateSet* state = mGeode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	osg::ref_ptr< osg::Point > pt = new osg::Point;
	pt->setSize( 10.f );
	state->setAttribute( pt.get() );

	//геометрической представление точки стало дочерним узлом MatrixTransform для того чтобы мы могли его перемещать
	m_MatrTr = new osg::MatrixTransform;
	m_MatrTr->addChild( mGeode.get() );
	m_MatrTr->setUpdateCallback( new UpdClbkLightPoint() );
}