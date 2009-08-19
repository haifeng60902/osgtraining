#include "TerrainPatchNode.h"

#include "PatchCullCallback.h"

#include <osg/BoundingBox>

TerrainPatchNode::TerrainPatchNode()
{
	m_rootNode = new osg::Group;

	//���������������� �������� ���� �����
	InitTerrainNode();	
}

TerrainPatchNode::~TerrainPatchNode()
{

}

void TerrainPatchNode::InitTerrainNode()
{
	//���������������� �������� ���� �����

	// ����������� ��������������� ������, ������ ����� 1024��(� 1 �� - 1024 �����), ������������ ������ 500�
	osg::BoundingBox bbox( 0, 0, 0, 1024 * 1024 , 1024 * 1024 , 500 );
	m_rootNode->setInitialBound( bbox );

	//�������� ����� ����������� ���������
	m_rootNode->setCullCallback( new PatchCullCallback );
}