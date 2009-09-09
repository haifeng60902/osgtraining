#include "GeometryPatch.h"

GeometryPatch::GeometryPatch( int x , int y , int sizeC , int scaleC )
{
	//������� ������ ��� �������� � ��� ���������
	m_patchGeom = new osg::Geometry;

	//������� ������ ������
	m_patchGeom->setVertexArray( CreateVertexArray( x , y , sizeC , scaleC ).get() );

	std::vector< unsigned int > m_vIndex;

	//��������� ������ ���������
	FillIndexVector( m_vIndex , sizeC );

	m_patchGeom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() , &m_vIndex[ 0 ] ) );
}

GeometryPatch::~GeometryPatch()
{

}

osg::ref_ptr<osg::Vec3Array> GeometryPatch::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{
	//������� ������ ������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	float kof = (float)scaleC / (float)( sizeC - 1 );

	//���������� ������� points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			v->push_back( osg::Vec3( x + j * kof , y + i * kof , 0 ) );
		}

	return v.get();
}

void GeometryPatch::FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC )
{
	//��������� ������ ���������
	_vIndex.push_back( 0 );
	_vIndex.push_back( sizeC );
	int count = sizeC - 1;
	int ind = 0;
	while( count > 0 )
	{
		for( int i = 0 ; i < count ; i++ )
		{
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] + 1 );
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] + 1 );
		}
		ind = _vIndex.size() - 3;
		_vIndex.push_back( _vIndex[ ind ] );
		count--;

		for( int i = 0 ; i< count ; i++ )
		{
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] + sizeC );
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] + sizeC );
		}

		ind = _vIndex.size() - 3;
		_vIndex.push_back( _vIndex[ ind ] );

		for( int i = 0 ; i < count ; i++ )
		{
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] - 1 );
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] - 1 );
		}

		ind = _vIndex.size() - 3;
		_vIndex.push_back( _vIndex[ ind ] );
		count--;

		for( int i=0 ; i < count ; i++ )
		{
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] - sizeC );
			ind = _vIndex.size() - 2;
			_vIndex.push_back( _vIndex[ ind ] - sizeC );
		}
		ind = _vIndex.size() - 3;
		_vIndex.push_back( _vIndex[ ind ] );
	}
}