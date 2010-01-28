#include "PerspectiveTexturePlane.h"

#include "binDef.h"
#include "UpdClbkPerspectiveTexturePlane.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

PerspectiveTexturePlane::PerspectiveTexturePlane()
{
	//создать геометрию
	CreateGeom();

	//добавить камеру
	AddCamera();

	//задать обратный вызов обновления для узла плоскости
	m_Transform->setUpdateCallback( new UpdClbkPerspectiveTexturePlane() );
}

PerspectiveTexturePlane::~PerspectiveTexturePlane()
{

}

void PerspectiveTexturePlane::CreateGeom()
{
	//создать геометрию
	osg::ref_ptr< osg::Geode > mGeode = new osg::Geode;

	//геометрия для прямоугольника
	osg::ref_ptr< osg::Geometry > mGeom = new osg::Geometry;

	//главная группа
	m_Transform = new osg::MatrixTransform;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	mGeom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( -HALF_SIZE , 1.0 , -HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( HALF_SIZE , 1.0 , -HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( HALF_SIZE , 1.0 , HALF_SIZE * WIN_H / WIN_W ) );
	v->push_back( osg::Vec3( -HALF_SIZE , 1.0 , HALF_SIZE * WIN_H / WIN_W ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	mGeom->setNormalArray( n.get() );
	mGeom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > c = new osg::Vec3Array;
	mGeom->setColorArray( c.get() );
	mGeom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec3( 1.f, 1.f, 1.f ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	mGeom->setTexCoordArray( 0, tc.get() );
	
	tc->push_back( osg::Vec2( 0 , 0 ) );
	tc->push_back( osg::Vec2( 1.0 , 0 ) );
	tc->push_back( osg::Vec2( 1.0 , 1.0 ) );
	tc->push_back( osg::Vec2( 0 , 1.0 ) );

	mGeom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	mGeode->addDrawable( mGeom.get() );

	m_Transform->addChild( mGeode.get() );
}

void PerspectiveTexturePlane::AddCamera()
{

	//добавить камеру
	m_Camera0.Init();

	//получить доступ к свойствам узла
	osg::StateSet* state = m_Transform->getOrCreateStateSet();

	//определить текстуру
	state->setTextureAttributeAndModes( 0 , m_Camera0.GetTexture().get() , osg::StateAttribute::ON );

	//выключаем освещение
	state->setMode( GL_LIGHTING , osg::StateAttribute::OFF );

	//добавить узел камеры
	m_Transform->addChild( m_Camera0.GetCameraNode().get() );
}