#include "GeometryTexturePatch.h"

GeometryTexturePatch::GeometryTexturePatch( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image )
{
	//создать объект для хранения в нем геометрии
	m_patchGeom = new osg::Geometry;

	//создать массив вершин
	m_patchGeom->setVertexArray( CreateVertexArray( x , y , sizeC , scaleC ).get() );

	//создать массив текстурных координат
	m_patchGeom->setTexCoordArray( 0, CreateTexCoordArray( x , y , sizeC , scaleC , 
		image->data() ).get() );

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	n->push_back( osg::Vec3( 0, -1, 0 ) );
	m_patchGeom->setNormalArray( n.get() );
	m_patchGeom->setNormalBinding( osg::Geometry::BIND_OVERALL );

	std::vector< unsigned int > m_vIndex;

	//заполнить вектор индексами
	FillIndexVector( m_vIndex , sizeC );

	m_patchGeom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() , &m_vIndex[ 0 ] ) );
}

GeometryTexturePatch::~GeometryTexturePatch()
{

}

osg::ref_ptr<osg::Vec3Array> GeometryTexturePatch::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{
	//создать массив вершин
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;

	float kof = (float)scaleC / (float)( sizeC - 1 );

	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			v->push_back( osg::Vec3( x + j * kof , y + i * kof , 0 ) );
		}

	return v.get();
}

osg::ref_ptr<osg::Vec2Array> GeometryTexturePatch::CreateTexCoordArray( int x , int y , int sizeC , 
																	   int scaleC , unsigned char *dataR )
{
	//создать массив текстурных координат
	osg::ref_ptr<osg::Vec2Array> tc0 = new osg::Vec2Array;

	float kof = (float)scaleC / (float)( sizeC - 1 );

	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			float indX = ( x + j * kof ) / 262144.0  * 512.0;
			float indY = ( y + i * kof ) / 262144.0  * 512.0;
			
			int iIndX = floor( indX );
			int iIndY = floor( indY );

			int r = dataR[ iIndY * 512 * 3 + iIndX * 3 ];
			int g = dataR[ iIndY * 512 * 3 + iIndX * 3 + 1];

			tc0->push_back( osg::Vec2( r / 16.0 + indX - iIndX , g / 16.0 + indY - iIndY ) );
		}

	return tc0.get();
}

void GeometryTexturePatch::FillIndexVector( std::vector< unsigned int > &_vIndex , int sizeC )
{
	//заполнить вектор индексами
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