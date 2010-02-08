#ifndef _LIGHT_POINT_H_
#define _LIGHT_POINT_H_

#include <osg/MatrixTransform>

class LightPoint
{
public:
	LightPoint();
	~LightPoint();

	//инициализация геометрического представления источника света
	void Init();

	//вернуть узел содержащий геометрическое представление источника света
	osg::ref_ptr< osg::MatrixTransform> GetPoint(){ return m_MatrTr.get(); };

private:
	osg::ref_ptr< osg::MatrixTransform > m_MatrTr;
};

#endif