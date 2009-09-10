#ifndef _TERRAIN_NODE_H_
#define _TERRAIN_NODE_H_

#include "TerrainPatchNode.h"
#include "TerrainSimplePatchNode.h"

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

class TerrainNode : public osg::Referenced
{
public:
	TerrainNode();
	~TerrainNode();

	//������� ���� ���������� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//���������������� �������� ���� �����
	void InitTerrainNode();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//osg::ref_ptr< TerrainPatchNode > m_TerrainPatch;

	osg::ref_ptr< TerrainSimplePatchNode > m_TerrainSimplePatch;
};

#endif	//_TERRAIN_NODE_H_