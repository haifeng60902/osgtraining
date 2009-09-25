#ifndef _TERRAIN_NODE_H_
#define _TERRAIN_NODE_H_

#include "TerrainShaderPatchNode.h"

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

	osg::ref_ptr< TerrainShaderPatchNode > m_TerrainShaderPatchNode;
};

#endif	//_TERRAIN_NODE_H_