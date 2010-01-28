#ifndef _PERSPECTIVE_TEXTURE_PLANE_H_
#define _PERSPECTIVE_TEXTURE_PLANE_H_

#include "CameraTexture0/CameraTexture0.h"

#include <osg/MatrixTransform>

class PerspectiveTexturePlane
{
public:
	PerspectiveTexturePlane();
	~PerspectiveTexturePlane();

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
	CameraTexture0 m_Camera0;

	//���� �������������
	osg::ref_ptr< osg::MatrixTransform > m_Transform;
};

#endif	//_PERSPECTIVE_TEXTURE_PLANE_H_