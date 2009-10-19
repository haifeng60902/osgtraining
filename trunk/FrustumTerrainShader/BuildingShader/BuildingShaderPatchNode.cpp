#include "BuildingShaderPatchNode.h"

#include "DynamicHouseUpdateCallback.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Image>
#include <osg/Texture2D>

BuildingShaderPatchNode::BuildingShaderPatchNode()
{
	m_rootNode = new osg::Group;

	//инициализировать корневой узел застройки
	InitBuildingNode();

	//динамически мен€емый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );

	osg::BoundingBox bbox( 0, 0, 0, 256.0 * 1024.0 , 256.0 * 1024.0 , 64 );
	m_rootNode->setInitialBound( bbox );
}

BuildingShaderPatchNode::~BuildingShaderPatchNode()
{

}

void BuildingShaderPatchNode::InitBuildingNode()
{
	//инициализировать корневой узел застройки

	//добавить шейдер
	AddShader();

	//задать обратный вызов обновлени€
	m_rootNode->setUpdateCallback( new DynamicHouseUpdateCallback );
}

void BuildingShaderPatchNode::AddShader()
{
	//добавить шейдер

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "building_geom" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/building_geom.vert" );
	LoadShaderSource( FragObj , "glsl/building_geom.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//настроить uniform'ы
	SetupUniforms( ss );
}

void BuildingShaderPatchNode::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void BuildingShaderPatchNode::SetupUniforms( osg::StateSet* ss )
{
	//настроить uniform'ы

	//добавление uniform'ов дл€ работы с текстурными модул€ми
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture2" , 2 ) );
}