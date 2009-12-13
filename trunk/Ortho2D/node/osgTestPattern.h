#ifndef _OSG_TEST_PATTERN_H_
#define _OSG_TEST_PATTERN_H_

#include <osg/Geode>

class osgTestPattern
{
public:
	osgTestPattern();
	~osgTestPattern();

	//������� ���� � ����������
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//������� ���������
	void CreateGeom();

	//��������� ����
	osg::ref_ptr< osg::Group > m_Group;
};

#endif	//_OSG_TEST_PATTERN_H_