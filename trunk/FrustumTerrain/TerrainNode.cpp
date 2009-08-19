#include "TerrainNode.h"

#include "TerrainCullCallback.h"

#include <osg/BoundingBox>

TerrainNode::TerrainNode()
{
	//������� ������� ����
	m_rootNode = new osg::Group;

	//���������������� �������� ���� �����
	InitTerrainNode();
}

TerrainNode::~TerrainNode()
{

}

void TerrainNode::InitTerrainNode()
{
	//���������������� �������� ���� �����

	// ����������� ��������������� ������, ������ ����� 1024��(� 1 �� - 1024 �����), ������������ ������ 500�
	osg::BoundingBox bbox( 0, 0, 0, 1024 * 1024 , 1024 * 1024 , 500 );
	m_rootNode->setInitialBound( bbox );

	//������ ����� ���������� ������� ���������
	m_rootNode->setCullCallback( new TerrainCullCallback );

	m_TerrainPatch = new TerrainPatchNode;

	//�������� ���� ������
	m_rootNode->addChild( m_TerrainPatch->getRootNode().get() );
}