#ifndef _OSG_PERSPECTIVE_TEXTURE_PLANE_H_
#define _OSG_PERSPECTIVE_TEXTURE_PLANE_H_

#include "NodeCameraTexture0/osgCameraNodeTexture0.h"

#include <osg/MatrixTransform>

class osgPerspectiveTexturePlane
{
public:
	osgPerspectiveTexturePlane();
	~osgPerspectiveTexturePlane();

	//������� ����
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_Transform.get(); };

private:
	//������� ���������
	void CreateGeom();

	//�������� ��������
	void AddTexture();

	//�������� ������
	void AddCamera();

	//����� ���������� �� ����������� � ��������
	osgCameraNodeTexture0 m_Camera0;

	//���� �������������
	osg::ref_ptr< osg::MatrixTransform > m_Transform;
};

#endif	//_OSG_PERSPECTIVE_TEXTURE_PLANE_H_