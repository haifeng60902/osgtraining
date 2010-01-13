#include "osgTexturePlane.h"

#include "../binDef.h"

#include "CameraUpdateCallback.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

osgTexturePlane::osgTexturePlane()
{
	//создать геометрию
	CreateGeom();

	//добавить текстуру
	//AddTexture();

	//добавить камеру
	AddCamera();
}

osgTexturePlane::~osgTexturePlane()
{

}

void osgTexturePlane::CreateGeom()
{
	//создать геометрию
	m_Geode = new osg::Geode;

	m_Geom = new osg::Geometry;

	//главная группа
	m_Group = new osg::Group;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	m_Geom->setVertexArray( v.get() );

	v->push_back( osg::Vec3( 0.0 , 0.0 , 0 ) );
	v->push_back( osg::Vec3( WIN_W , 0.0 , 0 ) );
	v->push_back( osg::Vec3( WIN_W , WIN_H , 0 ) );
	v->push_back( osg::Vec3( 0.0 , WIN_H , 0 ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	m_Geom->setNormalArray( n.get() );
	m_Geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, 0.f, 1.f ) );


	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > c = new osg::Vec3Array;
	m_Geom->setColorArray( c.get() );
	m_Geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec3( 1.f, 1.f, 1.f ) );


	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	m_Geom->setTexCoordArray( 0, tc.get() );
	double dW = 1.0 / ( 768.0f * 2.0f );
	double dH = 1.0 / ( 512.0f * 2.0f );
	tc->push_back( osg::Vec2( 0.0 + dW, 0.0 + dH ) );
	tc->push_back( osg::Vec2( 1.0 - dW, 0.0 + dH ) );
	tc->push_back( osg::Vec2( 1.0 - dW, 1.0 - dH ) );
	tc->push_back( osg::Vec2( 0.0 + dW, 1.0 - dH ) );

	m_Geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	m_Geode->addDrawable( m_Geom.get() );

	m_Group->addChild( m_Geode.get() );
}

void osgTexturePlane::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_Geode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "grass.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT ); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT );

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	//выключаем освещение
	state->setMode( GL_LIGHTING , osg::StateAttribute::OFF );
}

void osgTexturePlane::AddCamera()
{
	//добавить камеру

	//первый этап, создание текстуры в которую будет происходить отображение
	osg::Texture2D* texture = new osg::Texture2D;
	texture->setTextureSize( WIN_W , WIN_H );
	texture->setInternalFormat(GL_RGBA);
	texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	texture->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE); 
	texture->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE);

	texture->setResizeNonPowerOfTwoHint( false );

//////////////////////////////////////////////////////////////////////////
	//настройка состояния узла

	// new we need to add the texture to the Drawable, we do so by creating a 
	// StateSet to contain the Texture StateAttribute.
	osg::StateSet* state = m_Group->getOrCreateStateSet();

	//определить текстуру
	state->setTextureAttributeAndModes(0, texture,osg::StateAttribute::ON);

	//выключаем освещение
	state->setMode( GL_LIGHTING , osg::StateAttribute::OFF );

//////////////////////////////////////////////////////////////////////////
	//настройка камеры
	osg::Camera* camera = new osg::Camera;

	// set up the background color and clear mask.
	camera->setClearColor(osg::Vec4( 0.1f , 0.2f , 0.3f , 1.0f ));
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//настройка камеры
	camera->setProjectionMatrixAsPerspective( 45.0, WIN_W / WIN_H , 1.0 , 35000.0 );

	// set view
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	// set viewport
	camera->setViewport( 0 , 0 , WIN_W , WIN_H );

	// set the camera to render before the main camera.
	camera->setRenderOrder( osg::Camera::PRE_RENDER );
 
	// tell the camera to use OpenGL frame buffer object where supported.
	camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );

	// attach the texture and use it as the color buffer.
	camera->attach(osg::Camera::COLOR_BUFFER, texture, 
		0, 0, false,
		0, 0 );

	//загрузка тестового объекта
	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );
	osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/mi17/MI_17_lod.flt" );

	osg::StateSet* stateNode = camera->getOrCreateStateSet();

	//выключаем освещение
	stateNode->setMode( GL_LIGHTING , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE );

	camera->setUpdateCallback( new CameraUpdateCallback() );

	// add subgraph to render
	camera->addChild( node.get() );

	m_Group->addChild( camera );
}