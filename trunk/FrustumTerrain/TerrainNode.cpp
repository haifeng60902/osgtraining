#include "TerrainNode.h"

#include "TerrainCullCallback.h"

#include <osg/BoundingBox>

TerrainNode::TerrainNode()
{
	//создать главный узел
	m_rootNode = new osg::Group;

	//инициализировать корневой узел земли
	InitTerrainNode();
}

TerrainNode::~TerrainNode()
{

}

void TerrainNode::InitTerrainNode()
{
	//инициализировать корневой узел земли

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 1024 * 1024 , 1024 * 1024 , 500 );
	m_rootNode->setInitialBound( bbox );

	//задать класс вычисления области видимости
	m_rootNode->setCullCallback( new TerrainCullCallback );

	m_TerrainPatch = new TerrainPatchNode;

	//добавить узел ратчей
	m_rootNode->addChild( m_TerrainPatch->getRootNode().get() );
}