#ifndef _LIGHT_POINT_H_
#define _LIGHT_POINT_H_

#include <osg/Geode>

class LightPoint
{
public:
	LightPoint();
	~LightPoint();

	//инициализация геометрического представления источника света
	void Init();

	//вернуть узел содержащий геометрическое представление источника света
	osg::ref_ptr< osg::Geode > GetPoint(){ return m_Geode.get(); };

private:
	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif