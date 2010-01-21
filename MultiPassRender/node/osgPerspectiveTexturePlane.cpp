#include "osgPerspectiveTexturePlane.h"

#include "../binDef.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

osgPerspectiveTexturePlane::osgPerspectiveTexturePlane()
{
	//создать геометрию
	CreateGeom();

	//добавить текстуру
	AddTexture();
}

osgPerspectiveTexturePlane::~osgPerspectiveTexturePlane()
{

}

void osgPerspectiveTexturePlane::CreateGeom()
{
	//создать геометрию
	m_Geode = new osg::Geode;

	m_Geom = new osg::Geometry;

	//главная группа
	m_Group = new osg::Group;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	m_Geom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( WIN_W / WIN_H * 0.5 , 0.0 , -0.5 ) );
	v->push_back( osg::Vec3( -WIN_W / WIN_H * 0.5 , 0.0 , -0.5 ) );
	v->push_back( osg::Vec3( -WIN_W / WIN_H * 0.5 , 0.0 , 0.5 ) );
	v->push_back( osg::Vec3( WIN_W / WIN_H * 0.5 , 0.0 , 0.5 ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	m_Geom->setNormalArray( n.get() );
	m_Geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );


	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > c = new osg::Vec3Array;
	m_Geom->setColorArray( c.get() );
	m_Geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec3( 1.f, 1.f, 1.f ) );


	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	m_Geom->setTexCoordArray( 0, tc.get() );
	double dW = 1.0 / ( WIN_W * 2.0f );
	double dH = 1.0 / ( WIN_H * 2.0f );
	tc->push_back( osg::Vec2( 0.0 , 0.0 ) );
	tc->push_back( osg::Vec2( 1.0, 0.0 ) );
	tc->push_back( osg::Vec2( 1.0 , 1.0 ) );
	tc->push_back( osg::Vec2( 0.0 , 1.0 ) );

	m_Geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	m_Geode->addDrawable( m_Geom.get() );

	m_Group->addChild( m_Geode.get() );
}

void osgPerspectiveTexturePlane::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_Geode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "1680x1050.PNG" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST );
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST );
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE ); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE );

	tex0->setResizeNonPowerOfTwoHint( false );

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	//выключаем освещение
	state->setMode( GL_LIGHTING , osg::StateAttribute::OFF );
}
