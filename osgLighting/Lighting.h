#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Transform>

#include <vector>

class Lighting : public osg::Referenced
{
public:
	Lighting();
	virtual ~Lighting();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootGroup.get(); }

private:
	/*methods*/
	void buildScene();

	//загрузить модель
	osg::ref_ptr< osg::Node > LoadModel();

	//создать плоскость
	osg::ref_ptr< osg::Node > CreatePlane();

	//создать точку представляющую источник света
	osg::ref_ptr< osg::Geode > createLightPoint();

	//создать источник света
	osg::ref_ptr< osg::Transform > CreateLight();

	osg::ref_ptr< osg::Group > m_rootGroup;

	std::vector< unsigned int > m_vIndex;
};

#endif	//_LIGHTING_H_