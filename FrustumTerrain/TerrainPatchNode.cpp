#include "TerrainPatchNode.h"

#include "PatchCullCallback.h"

#include <osg/BoundingBox>

TerrainPatchNode::TerrainPatchNode()
{
	m_rootNode = new osg::Group;

	//инициализировать корневой узел земли
	InitTerrainNode();	
}

TerrainPatchNode::~TerrainPatchNode()
{

}

void TerrainPatchNode::InitTerrainNode()
{
	//инициализировать корневой узел земли

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 1024 * 1024 , 1024 * 1024 , 500 );
	m_rootNode->setInitialBound( bbox );

	//обратный вызов определения видимости
	m_rootNode->setCullCallback( new PatchCullCallback );
}