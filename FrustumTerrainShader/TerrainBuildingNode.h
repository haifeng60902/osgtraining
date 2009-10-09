#ifndef _TERRAIN_BUILDING_NODE_H_
#define _TERRAIN_BUILDING_NODE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

class TerrainBuildingNode : public osg::Referenced
{
public:
	TerrainBuildingNode();
	virtual ~TerrainBuildingNode();

	//вернуть узел содержащий части земли
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_TERRAIN_BUILDING_NODE_H_