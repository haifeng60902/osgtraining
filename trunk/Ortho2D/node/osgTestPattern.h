#ifndef _OSG_TEST_PATTERN_H_
#define _OSG_TEST_PATTERN_H_

#include <osg/Geode>

class osgTestPattern
{
public:
	osgTestPattern();
	~osgTestPattern();

	//вернуть узел с геометрией
	osg::ref_ptr< osg::Geode > GetNode(){ return m_Geode.get(); };

private:
	//создать геометрию
	void CreateGeom();

	//добавить текстуру
	void AddTexture();

	//геометрия узла
	osg::ref_ptr< osg::Group > m_Group;

	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif	//_OSG_TEST_PATTERN_H_