#include "TerrainNode.h"

#include "TerrainCullCallback.h"

#include <osg/BoundingBox>
#include <osg/PolygonMode>

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
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	m_rootNode->setInitialBound( bbox );

	//������ ����� ���������� ������� ���������
	m_rootNode->setCullCallback( new TerrainCullCallback );

	m_TerrainPatch = new TerrainPatchNode;

	//�������� ���� ������
	m_rootNode->addChild( m_TerrainPatch->getRootNode().get() );

	//�������� ����� ����������� 
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	state->setAttributeAndModes( polymode, osg::StateAttribute::ON );
}