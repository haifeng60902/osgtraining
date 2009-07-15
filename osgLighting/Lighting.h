#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

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

	//загрузить модель
	osg::ref_ptr< osg::Node >CreatePlane();

	osg::ref_ptr< osg::Group > m_rootGroup;
};

#endif	//_LIGHTING_H_