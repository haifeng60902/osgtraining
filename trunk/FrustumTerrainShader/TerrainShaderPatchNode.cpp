#include "TerrainShaderPatchNode.h"

#include "DynamicGroupUpdateCallback.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

TerrainShaderPatchNode::TerrainShaderPatchNode()
{
	m_rootNode = new osg::Group;

	//���������������� �������� ���� �����
	InitTerrainNode();

	//����������� �������� ����
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

TerrainShaderPatchNode::~TerrainShaderPatchNode()
{

}

void TerrainShaderPatchNode::InitTerrainNode()
{
	//���������������� �������� ���� �����

	//�������� ������
	AddShader();

	//������ �������� ����� ����������
	m_rootNode->setUpdateCallback( new DynamicGroupUpdateCallback( m_unfVisPos.get()) );
}

void TerrainShaderPatchNode::AddShader()
{
	//�������� ������

	//������������ ����� � ��������
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "only_geom" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/only_geom.vert" );
	LoadShaderSource( FragObj , "glsl/only_geom.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//���������� uniform'� ��� ������� �������� �����
	ss->addUniform( new osg::Uniform( "posOffset" , osg::Vec3( 0.0f ,0.0f , 0.0f ) ) );

	//���������� uniform'�� ��� ������� ��������� � ��������������� ������
	ss->addUniform( new osg::Uniform( "colorP" , osg::Vec3( 0.0f ,0.0f , 0.0f ) ) );
	ss->addUniform( new osg::Uniform( "colorS" , osg::Vec3( 0.0f ,0.0f , 0.0f ) ) );

	//��������� �����������
	m_unfVisPos = new osg::Uniform( "posVis" , osg::Vec3( 0.0f ,0.0f , 0.0f ) );
	ss->addUniform( m_unfVisPos.get() );
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
