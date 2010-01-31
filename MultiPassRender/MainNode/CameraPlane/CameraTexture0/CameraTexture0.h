#ifndef _CAMERA_TEXTURE_0_H_
#define _CAMERA_TEXTURE_0_H_

#include "TestFarPlane/TestFarPlanes.h"

#include <osg/Camera>
#include <osg/Texture2D>

class CameraTexture0
{
public:
	CameraTexture0();
	~CameraTexture0();

	//инициализация узла-камеры
	void Init();

	//вернуть узел с камерой
	osg::ref_ptr< osg::Camera > GetCameraNode(){ return m_Camera.get(); }

	//вернуть тестуру в которую происходит отображение
	osg::ref_ptr< osg::Texture2D > GetTexture(){ return m_Texture.get(); };

private:

	//создать текстуру
	void CreateTexture();

	//создание камеры
	void CreateCamera();

	//настройка узла камеры
	void SetupCameraNode();

	//добавить шейдер
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//узел камеры	
	osg::ref_ptr< osg::Camera > m_Camera;

	//узел с динамической текстурой
	osg::ref_ptr< osg::Texture2D > m_Texture;

	//тестовый плоскости для оценки правильности упаковки глубины
	TestFarPlanes m_TestFarPlanes;
};

#endif	//_CAMERA_TEXTURE_0_H_