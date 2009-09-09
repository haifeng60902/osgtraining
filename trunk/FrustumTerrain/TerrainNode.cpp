#include "TerrainNode.h"

#include "TerrainCullCallback.h"

#include <osg/BoundingBox>
#include <osg/PolygonMode>

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
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	m_rootNode->setInitialBound( bbox );

	//задать класс вычисления области видимости
	m_rootNode->setCullCallback( new TerrainCullCallback );

	m_TerrainPatch = new TerrainPatchNode;

	//добавить узел ратчей
	m_rootNode->addChild( m_TerrainPatch->getRootNode().get() );

	//добавить режим отображения 
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	state->setAttributeAndModes( polymode, osg::StateAttribute::ON );
}