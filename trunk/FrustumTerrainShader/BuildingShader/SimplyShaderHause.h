#ifndef _SYMPLY_SHADER_HAUSE_H_
#define _SYMPLY_SHADER_HAUSE_H_

#include "../binData/binPatch.h"

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Group>

class SimplyShaderHause : public osg::Referenced
{
public:
	SimplyShaderHause();

	//настроить внутренний uniform
	void SetupUniform( const binHouse &_house );

	//вернуть узел содержащий землю
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_SYMPLY_SHADER_HAUSE_H_