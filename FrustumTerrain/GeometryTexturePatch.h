#ifndef _GEOMETRY_TEXTURE_PATCH_H_
#define _GEOMETRY_TEXTURE_PATCH_H_

#include <osg/Geometry>
#include <osg/Image>

#include <vector>

class GeometryTexturePatch
{
public:
	//x,y - смещение €чейки, sizeC - количество сегментов, scaleC - размер €чейки
	GeometryTexturePatch( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image );

	~GeometryTexturePatch();

	osg::ref_ptr< osg::Geometry > GetGeometry(){ return m_patchGeom.get(); };
private:
	//создать массив вершин
	osg::ref_ptr<osg::Vec3Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//создать массив текстурных координат
	osg::ref_ptr<osg::Vec2Array> CreateTexCoordArray( int x , int y , int sizeC , int scaleC , unsigned char *dataR );

	//заполнить вектор индексами
	void FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC );

	//геометри€ €чейки
	osg::ref_ptr< osg::Geometry > m_patchGeom;
};

#endif	//_GEOMETRY_TEXTURE_PATCH_H_