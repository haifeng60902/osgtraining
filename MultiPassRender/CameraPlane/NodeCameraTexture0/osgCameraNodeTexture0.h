#ifndef _OSG_CAMERA_NODE_TEXTURE_0_H_
#define _OSG_CAMERA_NODE_TEXTURE_0_H_

#include <osg/Camera>
#include <osg/Texture2D>

class osgCameraNodeTexture0
{
public:
	osgCameraNodeTexture0();
	~osgCameraNodeTexture0();

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

	//узел камеры	
	osg::ref_ptr< osg::Camera > m_Camera;

	//узел с динамической текстурой
	osg::ref_ptr< osg::Texture2D > m_Texture; 
};

#endif	//_OSG_CAMERA_NODE_TEXTURE_0_H_