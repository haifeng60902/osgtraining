#include "TerrainShaderPatchNode.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

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

	//добавление uniform'а дл€ задани€ смещени€ патча
	ss->addUniform( new osg::Uniform( "posOffset" , osg::Vec3( 0,0,0) ) );
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
