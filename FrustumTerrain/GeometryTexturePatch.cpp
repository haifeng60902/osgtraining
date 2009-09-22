#include "GeometryTexturePatch.h"

GeometryTexturePatch::GeometryTexturePatch( int x , int y , int sizeC , int scaleC , osg::ref_ptr<osg::Image> image , double dAdd , double dScale )
{
	//сдвиг и масштабирование
	m_dAdd = dAdd;
	m_dScale = dScale;

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

	double kof = (double)scaleC / (double)( sizeC - 1.0 );

	double indX = (double)x / 262144.0 * 512.0;
	double indY = (double)y / 262144.0 * 512.0;

	int iIndX = indX;
	int iIndY = indY; 

	unsigned char r = dataR[ iIndY * 512 * 3 + iIndX * 3 ];
	unsigned char g = dataR[ iIndY * 512 * 3 + iIndX * 3 + 1];

	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
		{
			double addX = (double)j / ( (double)sizeC - 1.0 ) * ( 1.0 - m_dScale / 8192.0 );
			double addY = (double)i / ( (double)sizeC - 1.0 ) * ( 1.0 - m_dScale / 8192.0 );

			tc0->push_back( osg::Vec2( (double)r / 16.0 + addX * 256.0 / 4096.0 + m_dAdd / 8192.0, (double)g / 16.0 + addY * 256.0 / 4096.0 + m_dAdd / 8192.0 ) );
			//tc0->push_back( osg::Vec2( addX , addY ) );
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