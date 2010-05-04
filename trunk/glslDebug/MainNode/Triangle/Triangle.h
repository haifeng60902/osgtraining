#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/MatrixTransform>

class Triangle : public osg::Referenced
{
public:
	Triangle();
	~Triangle();

	//инициализация простой геометрии
	void Init();

	//вернуть узел с геометрией
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_Node.get(); };

private:
	//создать геометрию
	osg::ref_ptr< osg::Geode > CreateGeode();
	
	osg::ref_ptr< osg::MatrixTransform > m_Node;
};

#endif	//_TRIANGLE_H_