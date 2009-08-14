#ifndef _SIMPLE_SCENE_H_
#define _SIMPLE_SCENE_H_

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Image>

class SimpleScene : public osg::Referenced
{
public:
	SimpleScene();
	~SimpleScene();

	//������� ���� ���������� ���������
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//���������������� ���������
	void InitGeom();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_SIMPLE_SCENE_H_