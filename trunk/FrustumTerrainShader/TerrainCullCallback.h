#ifndef _TERRAIN_CULL_CALLBACK_H_
#define _TERRAIN_CULL_CALLBACK_H_

#include <osg/NodeCallback>
#include <osgUtil/CullVisitor>

class TerrainCullCallback : public osg::NodeCallback
{
public:
	TerrainCullCallback();
	~TerrainCullCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:
	//������ ������� �������� ��������� ���� ���
	bool m_bProj;
};

#endif	//_TERRAIN_CULL_CALLBACK_H_