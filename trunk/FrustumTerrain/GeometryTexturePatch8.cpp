#include "GeometryTexturePatch8.h"

#include <algorithm>

GeometryTexturePatch8::GeometryTexturePatch8( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image , double dAdd , double dScale )
{
	//����� � ���������������
	m_dAdd = dAdd;
	m_dScale = dScale;

	//������� ������ ��� �������� � ��� ���������
	m_patchGeom = new osg::Geometry;

	//������� ������ ������
	m_patchGeom->setVertexArray( CreateVertexArray( x , y , sizeC , scaleC ).get() );

	//������� ������ ���������� ���������
	m_patchGeom->setTexCoordArray( 0, CreateTexCoordArray( x , y , sizeC , scaleC , 
		image->data() ).get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	n->push_back( osg::Vec3( 0, -1, 0 ) );
	m_patchGeom->setNormalArray( n.get() );
	m_patchGeom->setNormalBinding( osg::Geometry::BIND_OVERALL );

	std::vector< unsigned int > m_vIndex;

	//��������� ������ ���������
	FillIndexVector( m_vIndex , sizeC );

	m_patchGeom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() , &m_vIndex[ 0 ] ) );
}

GeometryTexturePatch8::~GeometryTexturePatch8()
{

}

osg::ref_ptr<osg::Vec3Array> GeometryTexturePatch8::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{
	//������� ������ ������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	float kof = (float)scaleC / (float)( sizeC - 16 );

	//����� ������ � ������� ����� �����
	int iQuad = ( sizeC - 16 ) / 16 + 1;

	//�������� �� Y
	int iY = 0;

	//���������� ������� points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		//������ ����� ���� �������� �� 1 �� Y
		int shift = iQuad * ( iY + 1 );

		//���� i ��������� � iHalf �� ���������� �� 1 ����
		if ( i == shift )
			++iY;

		//�������� �� X
		int iX = 0;
		for (int j = 0 ; j < sizeC ; ++j )
		{
			//������ ����� ���� �������� �� 1 �� Y
			int shift = iQuad * ( iX + 1 );

			//���� j ��������� � iHalf �� ���������� �� 1 � ����
			if ( j == shift )
				++iX;

			v->push_back( osg::Vec3( x + ( j - iX ) * kof , y + ( i - iY ) * kof , 0 ) );
		}
	}

	return v.get();
}

osg::ref_ptr<osg::Vec2Array> GeometryTexturePatch8::CreateTexCoordArray( int x , int y , int sizeC , 
																		int scaleC , unsigned char *dataR )
{
	//������� ������ ���������� ���������
	osg::ref_ptr<osg::Vec2Array> tc0 = new osg::Vec2Array;

	double kof = (double)scaleC / (double)( sizeC - 16.0 );

	//�������� ���������� ���������
	std::pair< unsigned char , unsigned char > texOffset[16][16];

	//////////////////////////////////////////////////////////////////////////
	for ( int i = 0 ; i < 16 ; ++i )
	{
		double indY = ( (double)y + 512.0 * (double)i ) / 262144.0 * 512.0;
		int iIndY = indY;

		for ( int j = 0 ; j < 16 ; ++j )
		{
			double indX = ( (double)x + 512.0 * (double)j ) / 262144.0 * 512.0;
			int iIndX = indX;

			unsigned char r = dataR[ iIndY * 512 * 3 + iIndX * 3 ];
			unsigned char g = dataR[ iIndY * 512 * 3 + iIndX * 3 + 1];

			texOffset[ i ][ j ] = std::pair< unsigned char , unsigned char >( r , g );
		}
	}
	//////////////////////////////////////////////////////////////////////////

	//����� ������ � ������� ����� �����
	int iQuad = ( sizeC - 16 ) / 16 + 1;
	double dQuad = ( sizeC - 16.0 ) / 16.0;

	//�������� �� Y
	int iY = 0;
	double dY = 0.0;

	//���������� ������� points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		//������ ����� ���� �������� �� 1 �� Y
		int shift = iQuad * ( iY + 1 );

		//���� i ��������� � iHalf �� ���������� �� 1 ����
		if ( i == shift )
		{
			++iY;
			dY = iQuad * iY;
		}

		//������ �������� ���������� ���������( 16 ���� �� 0..1 )
		double addY = ( (double)i - dY ) / ( ( (double)iQuad - 1.0 ) * ( 1.0 - m_dScale / 8192.0 ) );

		//�������� �� X
		double iX = 0;
		double dX = 0.0;

		for ( int j = 0 ; j < sizeC ; ++j )
		{
			//������ ����� ���� �������� �� 1 �� Y
			int shift = iQuad * ( iX + 1 );

			//���� i ��������� � iHalf �� ���������� �� 1 ����
			if ( j == shift )
			{
				++iX;
				dX = iQuad * iX;
			}

			//������ �������� ���������� ���������( 16 ���� �� 0..1 )
			double addX = ( (double)j - dX ) / ( ( (double)iQuad - 1.0 ) * ( 1.0 - m_dScale / 8192.0 ) );

			unsigned char ucX = iX;
			unsigned char ucY = iY;

			unsigned char r = texOffset[ ucY ][ ucX ].first;
			unsigned char g = texOffset[ ucY ][ ucX ].second;

			tc0->push_back( osg::Vec2( (double)r / 16.0 + addX * 256.0 / 4096.0 + m_dAdd / 8192.0, (double)g / 16.0 + addY * 256.0 / 4096.0 + m_dAdd / 8192.0 ) );
			//tc0->push_back( osg::Vec2( addX , addY ) );
		}
	}

	return tc0.get();
}

void GeometryTexturePatch8::FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC )
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