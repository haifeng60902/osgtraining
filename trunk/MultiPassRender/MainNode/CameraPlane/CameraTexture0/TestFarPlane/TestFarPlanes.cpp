#include "TestFarPlanes.h"

#include <osg/Geometry>

#define PLANE_SIZE 1.5

#define PLANE_DEPTH 6.0

TestFarPlanes::TestFarPlanes()
{

}

TestFarPlanes::~TestFarPlanes()
{

}

void TestFarPlanes::Init()
{
//инициализация плоскостей

	//создать геометрию
	m_Geode = new osg::Geode;

	//геометрия для прямоугольника
	osg::ref_ptr< osg::Geometry > mGeom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	mGeom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( -PLANE_SIZE ,PLANE_DEPTH , -PLANE_SIZE ) );
	v->push_back( osg::Vec3( PLANE_SIZE , PLANE_DEPTH , -PLANE_SIZE ) );
	v->push_back( osg::Vec3( PLANE_SIZE , PLANE_DEPTH , PLANE_SIZE ) );
	v->push_back( osg::Vec3( -PLANE_SIZE , PLANE_DEPTH , PLANE_SIZE ) );

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

	mGeom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	m_Geode->addDrawable( mGeom.get() );
}