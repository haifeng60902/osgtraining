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

	//инициализация узла-камеры
	void Init();

	//вернуть узел с камерой
	osg::ref_ptr< osg::Camera > GetCameraNode(){ return m_Camera.get(); }

	//вернуть тестуру в которую происходит отображение
	osg::ref_ptr< osg::Texture2D > GetTexture0(){ return m_Texture0.get(); };

	//дать доступ к набору текстур
	tListTexture2D &GetListTextures(){ return m_ListTexture2D; };

private:

	//создать текстуру
	void CreateTexture();

	//создать текстуры
	void CreateTextures();

	//создание камеры
	void CreateCamera();

	//назначить текстуры камере
	void AttachTextures2Camera();

	//настройка узла камеры
	void SetupCameraNode();

	//добавить шейдер
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//узел камеры	
	osg::ref_ptr< osg::Camera > m_Camera;

	//узел с динамической текстурой
	osg::ref_ptr< osg::Texture2D > m_Texture0;

	//произвольный набор текстур
	tListTexture2D m_ListTexture2D;

	//тестовый плоскости для оценки правильности упаковки глубины
	TestFarPlanes m_TestFarPlanes;

	//геометрическое представление источника света
	LightPoint m_LightPoint;
};

#endif	//_CAMERA_TEXTURE_0_H_