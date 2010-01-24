#ifndef _OSG_PERSPECTIVE_TEXTURE_PLANE_H_
#define _OSG_PERSPECTIVE_TEXTURE_PLANE_H_

#include <osg/Geode>
#include <osg/Group>

class osgPerspectiveTexturePlane
{
public:
	osgPerspectiveTexturePlane();
	~osgPerspectiveTexturePlane();

	//������� ���� � ����������
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//������� ���������
	void CreateGeom();

	//�������� ��������
	void AddTexture();

	osg::ref_ptr< osg::Geode > m_Geode;

	//������� ������
	osg::ref_ptr< osg::Group > m_Group;

	//��������� ��� ��������������
	osg::ref_ptr< osg::Geometry > m_Geom;
};

#endif	//_OSG_PERSPECTIVE_TEXTURE_PLANE_H_