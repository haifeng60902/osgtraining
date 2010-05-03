#ifndef _MAIN_NODE_H_
#define _MAIN_NODE_H_

#include "Triangle/Triangle.h"

#include <osg/ref_ptr>
#include <osg/Group>

class osg::Group;

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

	//узел с простой геометрией треугольника
	osg::ref_ptr< Triangle > m_Triangle;
};

#endif	//_MAIN_NODE_H_