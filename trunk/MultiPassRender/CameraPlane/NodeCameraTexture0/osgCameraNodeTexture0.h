#ifndef _OSG_CAMERA_NODE_TEXTURE_0_H_
#define _OSG_CAMERA_NODE_TEXTURE_0_H_

#include <osg/Camera>
#include <osg/Texture2D>

class osgCameraNodeTexture0
{
public:
	osgCameraNodeTexture0();
	~osgCameraNodeTexture0();

	//������������� ����-������
	void Init();

	//������� ���� � �������
	osg::ref_ptr< osg::Camera > GetCameraNode(){ return m_Camera.get(); }

	//������� ������� � ������� ���������� �����������
	osg::ref_ptr< osg::Texture2D > GetTexture(){ return m_Texture.get(); };

private:

	//������� ��������
	void CreateTexture();

	//�������� ������
	void CreateCamera();

	//��������� ���� ������
	void SetupCameraNode();

	//���� ������	
	osg::ref_ptr< osg::Camera > m_Camera;

	//���� � ������������ ���������
	osg::ref_ptr< osg::Texture2D > m_Texture; 
};

#endif	//_OSG_CAMERA_NODE_TEXTURE_0_H_