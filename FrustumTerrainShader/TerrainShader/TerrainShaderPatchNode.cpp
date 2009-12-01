#include "TerrainShaderPatchNode.h"

#include "DynamicGroupUpdateCallback.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Image>
#include <osg/Texture2D>

TerrainShaderPatchNode::TerrainShaderPatchNode()
{
	m_rootNode = new osg::Group;

	//инициализировать корневой узел земли
	InitTerrainNode();

	//динамически мен€емый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

TerrainShaderPatchNode::~TerrainShaderPatchNode()
{

}

void TerrainShaderPatchNode::InitTerrainNode()
{
	//инициализировать корневой узел земли

	//добавить шейдер
	AddShader();

	//добавить текстуру с индексами
	AddTextureIndex();

	//добавить составную текстуру
	AddTexturePatches();

	//добавить текстуру дл€ микроландшафта
	AddMicroTexture( "grass_green-01_df_.dds" , 3 );

	//задать обратный вызов обновлени€
	m_rootNode->setUpdateCallback( new DynamicGroupUpdateCallback( m_unfVisPos.get()) );
}

void TerrainShaderPatchNode::AddTextureIndex()
{
	//добавить текстуру с индексами
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 =
		osgDB::readImageFile( "index.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	tex0->setFilter( osg::Texture::MIN_FILTER,osg::Texture::NEAREST );
	tex0->setFilter( osg::Texture::MAG_FILTER,osg::Texture::NEAREST );
	tex0->setWrap( osg::Texture::WRAP_S , osg::Texture::CLAMP ); 
	tex0->setWrap( osg::Texture::WRAP_T , osg::Texture::CLAMP ); 

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 1 , tex0.get() , osg::StateAttribute::ON );

	tex0->setUnRefImageDataAfterApply( true );
}

void TerrainShaderPatchNode::AddTexturePatches()
{
	//добавить составную текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 =
		osgDB::readImageFile( "big.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	tex0->setFilter( osg::Texture::MIN_FILTER,osg::Texture::NEAREST );
	tex0->setFilter( osg::Texture::MAG_FILTER,osg::Texture::NEAREST );
	tex0->setWrap( osg::Texture::WRAP_S , osg::Texture::CLAMP ); 
	tex0->setWrap( osg::Texture::WRAP_T , osg::Texture::CLAMP ); 

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 2.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	tex0->setUnRefImageDataAfterApply( true );
}

void TerrainShaderPatchNode::AddShader()
{
	//добавить шейдер

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "only_geom" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/only_geom.vert" );
	LoadShaderSource( FragObj , "glsl/only_geom.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//настроить uniform'ы
	SetupUniforms( ss );
}

void TerrainShaderPatchNode::SetupUniforms( osg::StateSet* ss )
{
	//настроить uniform'ы

	//положение наблюдател€
	m_unfVisPos = new osg::Uniform( "posVis" , osg::Vec3( 0.0f ,0.0f , 0.0f ) );
	ss->addUniform( m_unfVisPos.get() );
	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
	ss->addUniform( new osg::Uniform( "u_texture2" , 2 ) );

	ss->addUniform( new osg::Uniform( "u_texture3" , 3 ) );
	ss->addUniform( new osg::Uniform( "u_texture4" , 4 ) );
	ss->addUniform( new osg::Uniform( "u_texture5" , 5 ) );
	ss->addUniform( new osg::Uniform( "u_texture6" , 6 ) );
}

void TerrainShaderPatchNode::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void TerrainShaderPatchNode::AddMicroTexture( std::string _sFile , int _iMod )
{
	//добавить текстуру дл€ микроландшафта
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image =
		osgDB::readImageFile( _sFile.c_str() );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setImage( image.get() );

	tex->setFilter( osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setFilter( osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setWrap( osg::Texture::WRAP_S , osg::Texture::REPEAT ); 
	tex->setWrap( osg::Texture::WRAP_T , osg::Texture::REPEAT ); 

	state->setTextureAttributeAndModes( _iMod , tex.get() , osg::StateAttribute::ON );

	tex->setUnRefImageDataAfterApply( true );
}