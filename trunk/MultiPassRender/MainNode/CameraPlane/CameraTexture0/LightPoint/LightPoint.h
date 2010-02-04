#ifndef _LIGHT_POINT_H_
#define _LIGHT_POINT_H_

#include <osg/Geode>

class LightPoint
{
public:
	LightPoint();
	~LightPoint();

	//������������� ��������������� ������������� ��������� �����
	void Init();

	//������� ���� ���������� �������������� ������������� ��������� �����
	osg::ref_ptr< osg::Geode > GetPoint(){ return m_Geode.get(); };

private:
	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif