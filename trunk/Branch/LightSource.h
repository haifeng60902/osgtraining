#ifndef _LIGHT_SOURCE_H_
#define _LIGHT_SOURCE_H_

#include "LightSourceCallback.h"

#include <osg/Referenced>
#include <osg/Group>
#include <osg/ref_ptr>
#include <osg/Transform>

class LightSource : public osg::Referenced
{
public:
	LightSource();
	~LightSource();

	//вернуть узел света
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootGroup.get(); }

	//передать Uniform положения источника света
	void SetUniform( osg::Uniform *_LightPos ){ cb->SetUniform( _LightPos ); };

private:
	/*methods*/
	void buildScene();

	//создать точку представляющую источник света
	osg::ref_ptr< osg::Geode > createLightPoint();

	//создать источник света
	osg::ref_ptr< osg::Transform > CreateLight();

	//группа, содержащая геометрию источника света и сам свет
	osg::ref_ptr< osg::Group > m_rootGroup;

	LightSourceCallback *cb;
};

#endif	//_LIGHT_SOURCE_H_