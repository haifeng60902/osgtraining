#ifndef _CAMERA_TEXTURE_0_H_
#define _CAMERA_TEXTURE_0_H_

#include "TestFarPlane/TestFarPlanes.h"
#include "LightPoint/LightPoint.h"

#include <osg/Camera>
#include <osg/Texture2D>

#include <list>

class CameraTexture0
{
public:

	typedef std::list< osg::ref_ptr< osg::Texture2D > > tListTexture2D;

	CameraTexture0();
	~CameraTexture0();

	//������������� ����-������
	void Init();

	//������� ���� � �������
	osg::ref_ptr< osg::Camera > GetCameraNode(){ return m_Camera.get(); }

	//������� ������� � ������� ���������� �����������
	osg::ref_ptr< osg::Texture2D > GetTexture0(){ return m_Texture0.get(); };

	//���� ������ � ������ �������
	tListTexture2D &GetListTextures(){ return m_ListTexture2D; };

private:

	//������� ��������
	void CreateTexture();

	//������� ��������
	void CreateTextures();

	//�������� ������
	void CreateCamera();

	//��������� �������� ������
	void AttachTextures2Camera();

	//��������� ���� ������
	void SetupCameraNode();

	//�������� ������
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//���� ������	
	osg::ref_ptr< osg::Camera > m_Camera;

	//���� � ������������ ���������
	osg::ref_ptr< osg::Texture2D > m_Texture0;

	//������������ ����� �������
	tListTexture2D m_ListTexture2D;

	//�������� ��������� ��� ������ ������������ �������� �������
	TestFarPlanes m_TestFarPlanes;

	//�������������� ������������� ��������� �����
	LightPoint m_LightPoint;
};

#endif	//_CAMERA_TEXTURE_0_H_