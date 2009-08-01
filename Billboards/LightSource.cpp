#include "LightSource.h"

#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/Point>
#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osg/PolygonMode>
#include <osg/Material>
#include <osg/LightModel>

LightSource::LightSource()
{
	buildScene();
}

LightSource::~LightSource()
{

}

void LightSource::buildScene()
{
	// the root of our scenegraph.
	m_rootGroup = new osg::Group;

	m_rootGroup->addChild( CreateLight().get() );
}

osg::ref_ptr< osg::Transform > LightSource::CreateLight()
{
	//создать источник света
	osg::ref_ptr< osg::Geode > lightPoint = createLightPoint();

	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	osg::Matrix m;
	m.makeTranslate( osg::Vec3( 10.f, 0.f, 12.f ) );
	mt->setMatrix( m );

	// Create a mostly red light
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum( 0 );
	light->setPosition( osg::Vec4( 0.f, 0.f, 0.f, 1.f));
	light->setAmbient( osg::Vec4( 0.0f, 0.0f, 0.0f, 1.f));
	light->setDiffuse( osg::Vec4( 1.f, 1.0f, 1.0f, 1.f));
	light->setSpecular( osg::Vec4( 1.f, .1f, .1f, 1.f));

	light->setConstantAttenuation( 0.0001 );
	light->setLinearAttenuation( 0.0001 );
	light->setQuadraticAttenuation( 0.0001 );

	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
	mt->addChild( ls.get() );
	ls->setLight( light.get() );
	ls->addChild( lightPoint.get() );

	//динамически меняемый узел
	mt->setDataVariance( osg::Object::DYNAMIC );

	//обратный вызов, изменяющий положение источника света

	cb = new LightSourceCallback();

	mt->setUpdateCallback( cb );

	return mt.get();
}

osg::ref_ptr< osg::Geode > LightSource::createLightPoint()
{
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

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	osg::StateSet* state = geode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	osg::ref_ptr<osg::Point> pt = new osg::Point;
	pt->setSize( 10.f );
	state->setAttribute( pt.get() );

	return geode.get();
}
