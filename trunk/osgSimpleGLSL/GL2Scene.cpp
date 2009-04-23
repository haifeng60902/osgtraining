#include "GL2Scene.h"

#include "GL2SceneCallback.h"

#include <osg/Geode>
#include <osg/Node>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

static osg::ref_ptr<osg::Group> rootNode;

GL2Scene::GL2Scene()
{
	_rootNode = buildScene();

	_rootNode->setUpdateCallback( new GL2SceneCallback );

	AddShader();
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
	osg::ref_ptr< osg::Vec3Array > v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( -1.8f , 0.f , 0.8f ) );
	v->push_back( osg::Vec3( 1.8f , 0.f , 0.8f ) );
	v->push_back( osg::Vec3( 0.0f , 0.f , -0.8f ) );

	// Create an array of four colors.
	osg::ref_ptr< osg::Vec4Array > c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
	c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
	c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLES, 0, 3 ) );

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

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "shaders/Simple/C3E1v.vert" );
	LoadShaderSource( FragObj , "shaders/Simple/C2E2f.frag" );
	
	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	ss->addUniform( new osg::Uniform("_ZZ3SconstantColor", osg::Vec3(1.0f, 0.0f, 1.0f)) );
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