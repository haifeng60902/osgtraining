#include "osgTestPattern.h"

#include <osg/Geometry>

osgTestPattern::osgTestPattern()
{
	//геометрия узла
	m_Group = new osg::Group;

	//создать геометрию
	CreateGeom();

}

osgTestPattern::~osgTestPattern()
{

}

void osgTestPattern::CreateGeom()
{
	//создать геометрию
	m_Geode = new osg::Geode;

	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( -140 , -140 , 0 ) );
	v->push_back( osg::Vec3( 140 , -140 , 0 ) );
	v->push_back( osg::Vec3( 140 , 140 , 0 ) );

	v->push_back( osg::Vec3( -140 , 0 , -140 ) );
	v->push_back( osg::Vec3( 140 , 0 , -140 ) );
	v->push_back( osg::Vec3( 140 , 0 , 140 ) );
	
	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec4Array > c = new osg::Vec4Array;
	geom->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE );
	geom->setColorArray( c.get() );

	c->push_back( osg::Vec4( 1,0,0,1) );
	c->push_back( osg::Vec4( 1,1,0,1) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLES , 0, v->size() ) );

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -1000, -1000, -1000, 1000, 1000, 1000 );
	geom->setInitialBound( bbox );

	m_Geode->addDrawable( geom.get() );

	//m_Group->addChild( m_Geode.get() );
}