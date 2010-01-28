#ifndef _MAIN_NODE_H_
#define _MAIN_NODE_H_

#include "CameraPlane/PerspectiveTexturePlane.h"

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Group>

class MainNode : public osg::Referenced
{
public:
	MainNode();
	~MainNode();

	//инициализация данных
	void Init();

	//вернуть главный узел
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//корневой узел
	osg::ref_ptr< osg::Group > m_Group;

	//плоскость с динамической текстурой
	PerspectiveTexturePlane m_NodePlane;
};

#endif	//_MAIN_NODE_H_