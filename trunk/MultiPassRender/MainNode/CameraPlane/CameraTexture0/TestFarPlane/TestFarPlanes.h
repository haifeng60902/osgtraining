#ifndef _TEST_FAR_PLANES_H_
#define _TEST_FAR_PLANES_H_

#include <osg/Geode>

class TestFarPlanes
{
public:
	TestFarPlanes();
	~TestFarPlanes();

	//������������� ����������
	void Init();

	//������� ���� ���������� �������� ���������
	osg::ref_ptr< osg::Geode > GetPlane(){ return m_Geode.get(); };

private:
	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif	//_TEST_FAR_PLANES_H_