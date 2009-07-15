#include "DynamicTexture.h"

#include "DynamicTextureCallback.h"

#include <osg/Geode>
#include <osg/Node>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

DynamicTexture::DynamicTexture()
{
	buildScene();

	//установка callback'a для узла
	///_rootNode->setUpdateCallback( new GL2SceneCallback );

	//добавить текстуру
	AddTexture();
}

DynamicTexture::~DynamicTexture()
{

}

/*methods*/
void DynamicTexture::buildScene()
{
	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
	v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );
	tc->push_back( osg::Vec2( 0.f, 0.f ) );
	tc->push_back( osg::Vec2( 1.f, 0.f ) );
	tc->push_back( osg::Vec2( 1.f, 1.f ) );
	tc->push_back( osg::Vec2( 0.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	m_rootNode->addChild( geode.get() );

	//динамически меняемый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

void DynamicTexture::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	image0 = osgDB::readImageFile( "Images/Brick-Norman-Brown.TGA" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	//обновление узла
	m_rootNode->setUpdateCallback( new DynamicTextureCallback( image0.get() ) );
}