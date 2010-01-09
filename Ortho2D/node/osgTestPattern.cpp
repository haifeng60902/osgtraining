#include "osgTestPattern.h"

#include "../binDef.h"

#include <osg/Geometry>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Texture2D>

osgTestPattern::osgTestPattern()
{
	//геометри€ узла
	m_Group = new osg::Group;

	//создать геометрию
	CreateGeom();

	//добавить шейдер
	AddShader();

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

	v->push_back( osg::Vec3( 0.0 , 0.0 , 0 ) );
	v->push_back( osg::Vec3( WIN_W , 0.0 , 0 ) );
	v->push_back( osg::Vec3( WIN_W , WIN_H , 0 ) );
	v->push_back( osg::Vec3( 0.0 , WIN_H , 0 ) );
	
	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, 0.f, 1.f ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );
	double dW = 1.0 / ( 768.0f * 2.0f );
	double dH = 1.0 / ( 512.0f * 2.0f );
	tc->push_back( osg::Vec2( 0.0 + dW, 0.0 + dH ) );
	tc->push_back( osg::Vec2( 1.0 - dW, 0.0 + dH ) );
	tc->push_back( osg::Vec2( 1.0 - dW, 1.0 - dH ) );
	tc->push_back( osg::Vec2( 0.0 + dW, 1.0 - dH ) );
	
	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS , 0, v->size() ) );

	m_Geode->addDrawable( geom.get() );

	//m_Group->addChild( m_Geode.get() );
}

void osgTestPattern::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_Geode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 = osgDB::readImageFile( "640x480.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	tex0->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	tex0->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_EDGE); 
	tex0->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_EDGE);

	tex0->setResizeNonPowerOfTwoHint( false );

	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	state->setMode( GL_BLEND , osg::StateAttribute::OFF ); 
}

void osgTestPattern::AddShader()
{
	//добавить шейдер в сцену
	osg::StateSet* ss = m_Geode->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/ortho.vert" );
	LoadShaderSource( FragObj , "glsl/ortho.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
}

void osgTestPattern::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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