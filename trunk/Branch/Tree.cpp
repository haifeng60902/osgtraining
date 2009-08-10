#include "Tree.h"

#include "BranchXML.h"
#include "FrondsXML.h"
#include "LeafXML.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

Tree::Tree() : m_BrClbk( NULL )
{
	//�������� ���� ������
	m_rootNode = new osg::Group;

	//����, ���������� ��������� ������ � �����
	m_branchFrondsNode = new osg::Group;

	//����, ���������� ��������� ������
	m_leafNode = new osg::Group;

	m_rootNode->addChild( m_branchFrondsNode.get() );
	m_rootNode->addChild( m_leafNode.get() );

	//���������������� �����
	InitBranch();

	//���������������� �����
	InitFronds();

	//���������������� ������
	InitLeaf();

	//�������� ������ ��� ������ � �����
	AddShaderBranch();

	//�������� ������ ��� ������ � �����
	AddShaderLeaf();

	//�������� ���� �����
	m_rootNode->addChild( m_LightSource.getRootNode().get() );

	//����� ���������� ������ �����
	m_BrClbk = new BranchXMLWindCallback;
	m_rootNode->setUpdateCallback( m_BrClbk );

	//�������� uniform �������
	AddUniformMatrix();

}

Tree::~Tree()
{

}

void Tree::InitBranch()
{
	//���������������� �����
	osg::ref_ptr< BranchXML > branch = new BranchXML;

	//�������� ���� ������
	m_branchFrondsNode->addChild( branch->getBranchGeode() );
}

void Tree::InitFronds()
{
	//���������������� �����
	osg::ref_ptr< FrondsXML > fronds = new FrondsXML;

	//�������� ���� ������
	m_branchFrondsNode->addChild( fronds->getFrondsGeode() );
}

void Tree::InitLeaf()
{
	//���������������� ������

	osg::ref_ptr< LeafXML > leaf = new LeafXML;

	//�������� ���� ������
	m_leafNode->addChild( leaf->getLeafGeode() );
}

void Tree::AddShaderBranch()
{
	//�������� ������ ��� ������ � �����

	//������������ ����� � ��������
	osg::StateSet* ss = m_branchFrondsNode->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "branch_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/branch.vert" );
	LoadShaderSource( FragObj , "glsl/branch.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//���������� uniform'�� ��� ������ � ����������� ��������
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );

	//������������ ��������� ��������� �����
	m_LightPos = new osg::Uniform( "lightPos" , osg::Vec3(0,0,0) );

	ss->addUniform( m_LightPos );

	//�������� Uniform ��������� ��������� �����
	m_LightSource.SetUniform( m_LightPos );
}

void Tree::AddShaderLeaf()
{
	//�������� ������ ��� ������ � �����
	osg::StateSet* ss = m_leafNode->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "leaf_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/leaf.vert" );
	LoadShaderSource( FragObj , "glsl/leaf.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//���������� uniform'�� ��� ������ � ����������� ��������
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
	//�������� uniform �������

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

	//�������� ������ uniform ������
	m_BrClbk->SetUniformMatrix( vU );
}