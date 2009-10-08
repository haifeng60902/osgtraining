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

};

#endif	//_TERRAIN_BUILDING_NODE_H_