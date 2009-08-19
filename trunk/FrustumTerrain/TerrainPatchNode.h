#ifndef _TERRAIN_PATCH_NODE_H_
#define _TERRAIN_PATCH_NODE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

class TerrainPatchNode : public osg::Referenced
{
public:
	TerrainPatchNode();
	~TerrainPatchNode();

	//вернуть узел содержащий части земли
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать корневой узел земли
	void InitTerrainNode();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_TERRAIN_PATCH_NODE_H_