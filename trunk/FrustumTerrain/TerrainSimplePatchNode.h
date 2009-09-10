#ifndef _TERRAIN_SIMPLE_PATCH_NODE_H_
#define _TERRAIN_SIMPLE_PATCH_NODE_H_

#include "PatchCullCallback.h"

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geometry>
#include <osg/Program>

class TerrainSimplePatchNode : public osg::Referenced
{
public:
	TerrainSimplePatchNode();
	virtual ~TerrainSimplePatchNode();

	//������� ���� ���������� ����� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� �������� ���� �����
	void InitTerrainNode();

	//�������� �������� � �������
	void AddTextureTile();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_TERRAIN_SIMPLE_PATCH_NODE_H_