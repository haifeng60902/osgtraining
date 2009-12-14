#include "osgTestPattern.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

osgTestPattern::osgTestPattern()
{
	//геометрия узла
	m_Group = new osg::Group;

	//создать геометрию
	CreateGeom();

	//добавить текстуру
	AddTexture();
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

	v->push_back( osg::Vec3( -255.5 , -255.5 , 0 ) );
	v->push_back( osg::Vec3( 255.5 , -255.5 , 0 ) );
	v->push_back( osg::Vec3( 255.5 , 255.5 , 0 ) );
	v->push_back( osg::Vec3( -255.5 , 255.5 , 0 ) );
	
	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, 0.f, 1.f ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );
	double dO = 1.0 / 1024.0;
	tc->push_back( osg::Vec2( 0.0 + dO, 0.0 + dO) );
	tc->push_back( osg::Vec2( 1.0 - dO, 0.0 + dO ) );
	tc->push_back( osg::Vec2( 1.0 - dO, 1.0 - dO ) );
	tc->push_back( osg::Vec2( 0.0 + dO, 1.0 - dO ) );
	
	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	m_Geode->addDrawable( geom.get() );

	//m_Group->addChild( m_Geode.get() );
}

void osgTestPattern::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_Geode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "blackANDwhite.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE); 

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::OVERRIDE );

}