#ifndef _TEST_FAR_PLANES_H_
#define _TEST_FAR_PLANES_H_

#include <osg/Geode>

class TestFarPlanes
{
public:
	TestFarPlanes();
	~TestFarPlanes();

	//инициализация плоскостей
	void Init();

	//вернуть узел содержащий тестовые плоскости
	osg::ref_ptr< osg::Geode > GetPlane(){ return m_Geode.get(); };

private:
	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif	//_TEST_FAR_PLANES_H_