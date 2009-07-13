#include "GL2Scene.h"

#include "GL2SceneCallback.h"
#include "GL2SceneUniformCallback.h"

#include <osg/Geode>
#include <osg/Node>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/Image>

static osg::ref_ptr<osg::Group> rootNode;

GL2Scene::GL2Scene()
{
	_rootNode = buildScene();

	//установка callback'a для узла
	///_rootNode->setUpdateCallback( new GL2SceneCallback );

	//добавить шейдер
	AddShader();

	//добавить текстуру
	AddTexture();
}

GL2Scene::~GL2Scene()
{
}

osg::ref_ptr<osg::Group> GL2Scene::buildScene()
{
	// the root of our scenegraph.
	rootNode = new osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
	v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
	v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );

	// Create an array of four colors.
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
	c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
	c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );

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

	rootNode->addChild( geode.get() );

	return rootNode;
}

void GL2Scene::AddShader()
{
	//добавить шейдер в сцену
	osg::StateSet* ss = _rootNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/C3E1v.vert" );
	LoadShaderSource( FragObj , "glsl/C2E2f.frag" );
	
	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//создание параметра для передачи в шейдер
	osg::Uniform *_color = new osg::Uniform("_ZZ3SconstantColor", osg::Vec3(1.0f, 0.0f, 1.0f));

	//задание callback'a для динамического изменения параметра
	_color->setUpdateCallback( new GL2SceneUniformCallback );

	//добавление в состояние сцены
	ss->addUniform( _color );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
}  

void GL2Scene::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
{
	// load source from a file.
	std::string fqFileName = osgDB::findDataFile(fileName);
	if( fqFileName.length() != 0 )
	{
		shader->loadShaderSourceFromFile( fqFileName.c_str() );
	}
	else
	{
		osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
	}
}

void GL2Scene::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = _rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 =
		osgDB::readImageFile( "Images/osg128.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	// Load the texture image
	osg::ref_ptr<osg::Image> image1 =
		osgDB::readImageFile( "Images/blueFlowers.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex1 = new osg::Texture2D;
	tex1->setImage( image1.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 1, tex1.get() , osg::StateAttribute::ON );
}