#ifndef _OSG_TILED_PLANE_H_
#define _OSG_TILED_PLANE_H_

#include <osg/Geode>

class osgTiledPlane
{
public:
	osgTiledPlane();
	~osgTiledPlane();

	//вернуть узел с геометрией
	osg::ref_ptr< osg::Geode > GetNode(){ return m_Geode.get(); };

private:
	//создать геометрию
	void CreateGeom();

	//добавить текстуру
	void AddTexture();

	osg::ref_ptr< osg::Geode > m_Geode;
};

#endif	//_OSG_TILED_PLANE_H_