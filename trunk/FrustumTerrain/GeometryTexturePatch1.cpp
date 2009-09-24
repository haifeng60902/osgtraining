#include "GeometryTexturePatch1.h"

GeometryTexturePatch1::GeometryTexturePatch1( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image , double dAdd , double dScale )
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

GeometryTexturePatch1::~GeometryTexturePatch1()
{

}

osg::ref_ptr<osg::Vec3Array> GeometryTexturePatch1::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{
	//������� ������ ������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	float kof = (float)scaleC / (float)( sizeC - 2 );

	//����� ������ � ������� ����� �����
	int iHalf = ( sizeC - 2 ) / 2 + 1;

	//�������� �� Y
	float fY = 0;

	//���������� ������� points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		//���� i ��������� � iHalf �� ���������� �� 1 ����
		if ( i == iHalf )
			++fY;

		//�������� �� X
		float fX = 0;
		for (int j = 0 ; j < sizeC ; ++j )
		{
			//���� j ��������� � iHalf �� ���������� �� 1 � ����
			if ( j == iHalf )
				++fX;
			
			v->push_back( osg::Vec3( x + ( j - fX ) * kof , y + ( i - fY ) * kof , 0 ) );
		}
	}

	return v.get();
}

osg::ref_ptr<osg::Vec2Array> GeometryTexturePatch1::CreateTexCoordArray( int x , int y , int sizeC , 
																	   int scaleC , unsigned char *dataR )
{
	//������� ������ ���������� ���������
	osg::ref_ptr<osg::Vec2Array> tc0 = new osg::Vec2Array;

	double kof = (double)scaleC / (double)( sizeC - 2.0 );

	//////////////////////////////////////////////////////////////////////////
	double indX0 = (double)x / 262144.0 * 512.0;
	double indY0 = (double)y / 262144.0 * 512.0;

	double indX1 = ( (double)x + 512.0 ) / 262144.0 * 512.0;
	double indY1 = (double)y / 262144.0 * 512.0;

	double indX2 = ( (double)x + 512.0 ) / 262144.0 * 512.0;
	double indY2 = ( (double)y + 512.0 ) / 262144.0 * 512.0;

	double indX3 = (double)x / 262144.0 * 512.0;
	double indY3 = ( (double)y + 512.0 ) / 262144.0 * 512.0;

	//////////////////////////////////////////////////////////////////////////
	int iIndX0 = indX0;
	int iIndY0 = indY0; 

	int iIndX1 = indX1;
	int iIndY1 = indY1; 

	int iIndX2 = indX2;
	int iIndY2 = indY2; 

	int iIndX3 = indX3;
	int iIndY3 = indY3; 

	//////////////////////////////////////////////////////////////////////////
	unsigned char r0 = dataR[ iIndY0 * 512 * 3 + iIndX0 * 3 ];
	unsigned char g0 = dataR[ iIndY0 * 512 * 3 + iIndX0 * 3 + 1];

	unsigned char r1 = dataR[ iIndY1 * 512 * 3 + iIndX1 * 3 ];
	unsigned char g1 = dataR[ iIndY1 * 512 * 3 + iIndX1 * 3 + 1];

	unsigned char r2 = dataR[ iIndY2 * 512 * 3 + iIndX2 * 3 ];
	unsigned char g2 = dataR[ iIndY2 * 512 * 3 + iIndX2 * 3 + 1];

	unsigned char r3 = dataR[ iIndY3 * 512 * 3 + iIndX3 * 3 ];
	unsigned char g3 = dataR[ iIndY3 * 512 * 3 + iIndX3 * 3 + 1];

	//����� ������ � ������� ����� �����
	int iHalf = ( sizeC - 2 ) / 2 + 1;
	double dHalf = ( sizeC - 2.0 ) / 2.0;

	double dY = 0.0;

	unsigned char g = g0;

	//���������� ������� points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		if ( iHalf == i )
			dY = iHalf;

		//������ �������� ���������� ���������( 2 ���� �� 0..1 )
		double addY = ( (double)i - dY ) / ( dHalf * ( 1.0 - m_dScale / 8192.0 ) );

		double dX = 0.0;

		unsigned char r = r0;

		for ( int j = 0 ; j < sizeC ; ++j )
		{
			if ( iHalf == j )
				dX = iHalf;

	//////////////////////////////////////////////////////////////////////////
			if ( ( dX == 0.0 ) && ( dY == 0.0 ) )
			{
				r = r0;
				g = g0;
			}
			else
				if ( ( dX == iHalf ) && (dY == 0.0 ) )
				{
					r = r1;
					g = g1;
				}
				else
					if ( ( dX == iHalf ) && ( dY == iHalf ) )
					{
						r = r2;
						g = g2;
					}
					else
						if ( ( dX == 0.0 ) && ( dY == iHalf ) )
						{
							r = r3;
							g = g3;
						}
	//////////////////////////////////////////////////////////////////////////

			double addX = ( (double)j - dX ) / ( dHalf * ( 1.0 - m_dScale / 8192.0 ) );

			tc0->push_back( osg::Vec2( (double)r / 16.0 + addX * 256.0 / 4096.0 + m_dAdd / 8192.0, (double)g / 16.0 + addY * 256.0 / 4096.0 + m_dAdd / 8192.0 ) );
			//tc0->push_back( osg::Vec2( addX , addY ) );
		}
	}

	return tc0.get();
}

void GeometryTexturePatch1::FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC )
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