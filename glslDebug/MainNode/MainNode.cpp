#include "MainNode.h"

#include "UpdClbkMainNode.h"

#include <osgDB/ReadFile>
#include <osg/Referenced>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>

MainNode::MainNode()
{

}

MainNode::~MainNode()
{

}

void MainNode::Init()
{
//инициализаци€ данных
	
	m_Group = new osg::Group;

	osg::StateSet* ss = m_Group->getOrCreateStateSet();

	//добавить шейдер в сцену
	AddShader( ss ); 

	//osg::ref_ptr< osg::Node > node = osgDB::readNodeFile( "flt/sphere/sphere.flt" );

	//добавить тестовую геометрию
	//m_Group->addChild( node.get() );

	m_Triangle = new Triangle();
	m_Triangle->Init();
	m_Group->addChild( m_Triangle->GetNode().get() );

	//задать обратный вызов обновлени€ главного узла дл€ расчета параметров камеры
	m_Group->setUpdateCallback( new UpdClbkMainNode() );
}

void MainNode::AddShader( osg::StateSet* ss )
{
	//добавить шейдер в сцену

	//создать экземпл€р программы
	osg::Program* program = new osg::Program;
	program->setName( "microshader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/simple.vert" );
	LoadShaderSource( FragObj , "glsl/simple.frag" );

	ss->setAttributeAndModes( program , osg::StateAttribute::ON );
}

void MainNode::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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