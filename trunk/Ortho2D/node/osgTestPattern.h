#ifndef _OSG_TEST_PATTERN_H_
#define _OSG_TEST_PATTERN_H_

#include <osg/Geode>

class osgTestPattern
{
public:
	osgTestPattern();
	~osgTestPattern();

	//вернуть узел с геометрией
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//создать геометрию
	void CreateGeom();

	//геометрия узла
	osg::ref_ptr< osg::Group > m_Group;
};

#endif	//_OSG_TEST_PATTERN_H_