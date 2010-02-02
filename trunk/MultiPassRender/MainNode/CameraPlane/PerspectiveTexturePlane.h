#ifndef _PERSPECTIVE_TEXTURE_PLANE_H_
#define _PERSPECTIVE_TEXTURE_PLANE_H_

#include "CameraTexture0/CameraTexture0.h"

#include <osg/MatrixTransform>

class PerspectiveTexturePlane
{
public:
	PerspectiveTexturePlane();
	~PerspectiveTexturePlane();

	//вернуть узел
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_Transform.get(); };

private:
	//создать геометрию
	void CreateGeom();

	//добавить текстуры
	void AddTextures( osg::StateSet* state );

	//добавить камеру
	void AddCamera();

	//добавить шейдер
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//класс отвечающий за отображение в текстуру
	CameraTexture0 m_Camera0;

	//узел трансформации
	osg::ref_ptr< osg::MatrixTransform > m_Transform;
};

#endif	//_PERSPECTIVE_TEXTURE_PLANE_H_