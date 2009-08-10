#include "Tree.h"

#include "BranchXML.h"
#include "FrondsXML.h"
#include "LeafXML.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

Tree::Tree() : m_BrClbk( NULL )
{
	//корневой узел дерева
	m_rootNode = new osg::Group;

	//узел, содержащий геометрию ствола и веток
	m_branchFrondsNode = new osg::Group;

	//узел, содержащий геометрию листвы
	m_leafNode = new osg::Group;

	m_rootNode->addChild( m_branchFrondsNode.get() );
	m_rootNode->addChild( m_leafNode.get() );

	//инициализировать ствол
	InitBranch();

	//инициализировать ветки
	InitFronds();

	//инициализировать листву
	InitLeaf();

	//добавить шейдер для ствола в сцену
	AddShaderBranch();

	//добавить шейдер для листвы в сцену
	AddShaderLeaf();

	//добавить узел света
	m_rootNode->addChild( m_LightSource.getRootNode().get() );

	//класс обновления матриц ветра
	m_BrClbk = new BranchXMLWindCallback;
	m_rootNode->setUpdateCallback( m_BrClbk );

	//добавить uniform матрицы
	AddUniformMatrix();

}

Tree::~Tree()
{

}

void Tree::InitBranch()
{
	//инициализировать ствол
	osg::ref_ptr< BranchXML > branch = new BranchXML;

	//добавить узел ствола
	m_branchFrondsNode->addChild( branch->getBranchGeode() );
}

void Tree::InitFronds()
{
	//инициализировать ветки
	osg::ref_ptr< FrondsXML > fronds = new FrondsXML;

	//добавить узел ствола
	m_branchFrondsNode->addChild( fronds->getFrondsGeode() );
}

void Tree::InitLeaf()
{
	//инициализировать листву

	osg::ref_ptr< LeafXML > leaf = new LeafXML;

	//добавить узел листвы
	m_leafNode->addChild( leaf->getLeafGeode() );
}

void Tree::AddShaderBranch()
{
	//добавить шейдер для ствола в сцену

	//формирование сцены с шейдером
	osg::StateSet* ss = m_branchFrondsNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "branch_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/branch.vert" );
	LoadShaderSource( FragObj , "glsl/branch.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );

	//динамическое положение источника света
	m_LightPos = new osg::Uniform( "lightPos" , osg::Vec3(0,0,0) );

	ss->addUniform( m_LightPos );

	//передать Uniform положения источника света
	m_LightSource.SetUniform( m_LightPos );
}

void Tree::AddShaderLeaf()
{
	//добавить шейдер для листвы в сцену
	osg::StateSet* ss = m_leafNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "leaf_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/leaf.vert" );
	LoadShaderSource( FragObj , "glsl/leaf.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );

	ss->addUniform( m_LightPos );
}

void Tree::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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

void Tree::AddUniformMatrix()
{
	//добавить uniform матрицы

	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	osg::Matrix m;

	std::vector< osg::Uniform* > vU;

	vU.push_back( new osg::Uniform( "wRot0" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot1" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot2" , m ) );
	ss->addUniform( vU.back() );
	vU.push_back( new osg::Uniform( "wRot3" , m ) );
	ss->addUniform( vU.back() );

	//передать вектор uniform матриц
	m_BrClbk->SetUniformMatrix( vU );
}