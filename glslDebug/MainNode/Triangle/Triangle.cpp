#include "Triangle.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

void Triangle::Init()
{
	//инициализация простой геометрии
	
	//создать геометрию
	m_Geode = new osg::Geode;

	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( -3 , 3 , -3 ) );
	v->push_back( osg::Vec3( 3 , 3 , -3 ) );
	v->push_back( osg::Vec3( 0 , 3 , 3 ) );
	
	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );


	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > c = new osg::Vec3Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec3( 1.f, 1.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLES , 0, v->size() ) );

	m_Geode->addDrawable( geom.get() );
}