#ifndef _TERRAIN_PATCH_NODE_H_
#define _TERRAIN_PATCH_NODE_H_

#include "PatchCullCallback.h"

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geometry>
#include <osg/Program>

class TerrainPatchNode : public osg::Referenced
{
public:
	TerrainPatchNode();
	~TerrainPatchNode();

	//������� ���� ���������� ����� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� �������� ���� �����
	void InitTerrainNode();

	//������� ��������
	void CreateGeometry();

	//������� ��������, ���������� �������� ���������
	void CreateTexture();

	//�������� ������ � ����
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	float GetFloatRand();

	//������� ��������� ���������
	osg::ref_ptr< osg::Geometry > CreateGeometry( int x , int y );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	osg::ref_ptr< PatchCullCallback > m_rpPatchCullCallback;
};

#endif	//_TERRAIN_PATCH_NODE_H_