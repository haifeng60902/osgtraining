#include "TerrainNode.h"

#include <osg/BoundingBox>
#include <osg/PolygonMode>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

TerrainNode::TerrainNode()
{
	//������� ������� ����
	m_rootNode = new osg::Group;

	//���������������� �������� ���� �����
	InitTerrainNode();

	//���������������� �������� ���� ��������
	InitBuildingNode();

	//�������� �������� � ������ �����
	AddTextureHeightmap();

	//�������� ����� ����������� 
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	//state->setAttributeAndModes( polymode, osg::StateAttribute::ON );

	//����������� �������� ����
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

TerrainNode::~TerrainNode()
{

}

void TerrainNode::InitTerrainNode()
{
	//���������������� �������� ���� �����

	// ����������� ��������������� ������, ������ ����� 256��(� 1 �� - 1024 �����), ������������ ������ 500�
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	m_rootNode->setInitialBound( bbox );

	//����� ���������� �� ������������ � ����� ������ �����������
	m_TerrainShaderPatchNode = new TerrainShaderPatchNode;

	//�������� ���� ������
	m_rootNode->addChild( m_TerrainShaderPatchNode->getRootNode().get() );
}

void TerrainNode::InitBuildingNode()
{
	//���������������� �������� ���� ��������

	//����� ���������� �� ������������ � ����� ������ �����������
	m_BuildingShaderPatchNode = new BuildingShaderPatchNode;

	//�������� ���� �� ����������
	m_rootNode->addChild( m_BuildingShaderPatchNode->getRootNode().get() );
}

void TerrainNode::AddTextureHeightmap()
{
	//�������� �������� � ������ �����
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 =
		osgDB::readImageFile( "terHightmap.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex2 = new osg::Texture2D;
	tex2->setImage( image0.get() );

	tex2->setFilter( osg::Texture::MIN_FILTER,osg::Texture::LINEAR );
	tex2->setFilter( osg::Texture::MAG_FILTER,osg::Texture::LINEAR );
	tex2->setWrap( osg::Texture::WRAP_S , osg::Texture::REPEAT ); 
	tex2->setWrap( osg::Texture::WRAP_T , osg::Texture::REPEAT ); 

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 2, tex2.get() , osg::StateAttribute::ON );

	tex2->setUnRefImageDataAfterApply( true );
}