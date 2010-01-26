#ifndef _OSG_PERSPECTIVE_TEXTURE_PLANE_H_
#define _OSG_PERSPECTIVE_TEXTURE_PLANE_H_

#include "NodeCameraTexture0/osgCameraNodeTexture0.h"

#include <osg/MatrixTransform>

class osgPerspectiveTexturePlane
{
public:
	osgPerspectiveTexturePlane();
	~osgPerspectiveTexturePlane();

	//вернуть узел
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_Transform.get(); };

private:
	//создать геометрию
	void CreateGeom();

	//добавить текстуру
	void AddTexture();

	//добавить камеру
	void AddCamera();

	//класс отвечающий за отображение в текстуру
	osgCameraNodeTexture0 m_Camera0;

	//узел трансформации
	osg::ref_ptr< osg::MatrixTransform > m_Transform;
};

#endif	//_OSG_PERSPECTIVE_TEXTURE_PLANE_H_