#ifndef _GEOMETRY_PATCH_H_
#define _GEOMETRY_PATCH_H_

#include <osg/Geometry>

#include <vector>

class GeometryPatch
{
public:
	//x,y - �������� ������, sizeC - ���������� ���������, scaleC - ������ ������
	GeometryPatch( int x , int y , int sizeC , int scaleC );

	~GeometryPatch();

	osg::ref_ptr< osg::Geometry > GetGeometry(){ return m_patchGeom.get(); };
private:
	//������� ������ ������
	osg::ref_ptr<osg::Vec3Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//��������� ������ ���������
	void FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC );

	//��������� ������
	osg::ref_ptr< osg::Geometry > m_patchGeom;
};

#endif	//_GEOMETRY_PATCH_H_