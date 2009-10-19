#include "BuildingShaderPatchNode.h"

#include "DynamicHouseUpdateCallback.h"

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Image>
#include <osg/Texture2D>

BuildingShaderPatchNode::BuildingShaderPatchNode()
{
	m_rootNode = new osg::Group;

	//���������������� �������� ���� ���������
	InitBuildingNode();

	//����������� �������� ����
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );

	osg::BoundingBox bbox( 0, 0, 0, 256.0 * 1024.0 , 256.0 * 1024.0 , 64 );
	m_rootNode->setInitialBound( bbox );
}

BuildingShaderPatchNode::~BuildingShaderPatchNode()
{

}

void BuildingShaderPatchNode::InitBuildingNode()
{
	//���������������� �������� ���� ���������

	//�������� ������
	AddShader();

	//������ �������� ����� ����������
	m_rootNode->setUpdateCallback( new DynamicHouseUpdateCallback );
}

void BuildingShaderPatchNode::AddShader()
{
	//�������� ������

	//������������ ����� � ��������
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//������� ��������� ���������
	osg::Program* program = new osg::Program;
	program->setName( "building_geom" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/building_geom.vert" );
	LoadShaderSource( FragObj , "glsl/building_geom.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//��������� uniform'�
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
	//��������� uniform'�

	//���������� uniform'�� ��� ������ � ����������� ��������
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture2" , 2 ) );
}