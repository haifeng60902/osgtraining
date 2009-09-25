#ifndef _GEOMETRY_TEXTURE_PATCH_32_H_
#define _GEOMETRY_TEXTURE_PATCH_32_H_

#include <osg/Geometry>
#include <osg/Image>

#include <vector>

class GeometryTexturePatch32
{
public:
	//x,y - смещение €чейки, sizeC - количество сегментов, scaleC - размер €чейки
	GeometryTexturePatch32( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image , double fAdd , double dScale );

	~GeometryTexturePatch32();

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

	//сдвиг и масштабирование
	double m_dAdd;
	double m_dScale;
};

#endif	//_GEOMETRY_TEXTURE_PATCH_32_H_