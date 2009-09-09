#ifndef _GEOMETRY_PATCH_H_
#define _GEOMETRY_PATCH_H_

#include <osg/Geometry>

#include <vector>

class GeometryPatch
{
public:
	//x,y - смещение €чейки, sizeC - количество сегментов, scaleC - размер €чейки
	GeometryPatch( int x , int y , int sizeC , int scaleC );

	~GeometryPatch();

	osg::ref_ptr< osg::Geometry > GetGeometry(){ return m_patchGeom.get(); };
private:
	//создать массив вершин
	osg::ref_ptr<osg::Vec3Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//заполнить вектор индексами
	void FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC );

	//геометри€ €чейки
	osg::ref_ptr< osg::Geometry > m_patchGeom;
};

#endif	//_GEOMETRY_PATCH_H_