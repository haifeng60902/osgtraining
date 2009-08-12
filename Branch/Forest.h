#ifndef _FOREST_H_
#define _FOREST_H_

#include "BranchXML.h"

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>

class Forest : public osg::Referenced
{
public:
	Forest();
	~Forest();

	//вернуть узел содержащий лес
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициализировать стволы
	void InitBranches();

	//инициализировать ветки леса
	void InitFronds();

	//задать положение через uniform
	void SetPos( osg::StateSet *ss , float i , float j );

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_FOREST_H_