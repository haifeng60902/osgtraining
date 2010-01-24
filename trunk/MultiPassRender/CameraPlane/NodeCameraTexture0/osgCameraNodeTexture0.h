#ifndef _OSG_CAMERA_NODE_TEXTURE_0_H_
#define _OSG_CAMERA_NODE_TEXTURE_0_H_

#include <osg/Camera>

class osgCameraNodeTexture0
{
public:
	osgCameraNodeTexture0();
	~osgCameraNodeTexture0();

	//������������� ����-������
	void Init();

	//������� ���� � �������
	osg::ref_ptr< osg::Camera > GetCameraNode(){ m_Camera.get(); }

private:
	//���� ������	
	osg::ref_ptr< osg::Camera > m_Camera;
};

#endif	//_OSG_CAMERA_NODE_TEXTURE_0_H_