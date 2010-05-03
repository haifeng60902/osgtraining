#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <osg/ref_ptr>
#include <osg/Geode>

class Triangle : public osg::Referenced
{
public:
	Triangle();
	~Triangle();

	//инициализация простой геометрии
	void Init();

	//вернуть узел с геометрией
	osg::ref_ptr< osg::Geode > GetNode(){ return m_Geode.get(); };

private:
	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif	//_TRIANGLE_H_