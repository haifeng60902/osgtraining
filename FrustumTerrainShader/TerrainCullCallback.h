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
	//расчет матрицы проекции выполнить один раз
	bool m_bProj;
};

#endif	//_TERRAIN_CULL_CALLBACK_H_