#include "DynamicGroupLevel16384Node.h"

#include <osg/Geometry>

#include <iostream>

DynamicGroupLevel16384Node::DynamicGroupLevel16384Node() : m_iCount( 0 )
{
	//зарезервировать память для 64 узлов
	m_vData.resize( 64 );

	//группа узлов
	m_rootNode = new osg::Group;

	//инициализировать геометрию патчей земной поверхности
	InitGeodes();

	//узел динамически меняет количество потомков
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

void DynamicGroupLevel16384Node::InitGeodes()
{
	//инициализировать геометрию патчей земной поверхности

	for ( int i = 0 ; i < m_vData.size() ; ++i )
	{
		//добавить узел геометрии
		m_vData[ i ].m_Geode = new osg::Geode;

		//добавить uniform
		m_vData[ i ].m_unfOffset = new osg::Uniform( m_vData[ i ].m_sOffset.c_str() , osg::Vec3( 0,0,0) );
		m_vData[ i ].m_unfColorP = new osg::Uniform( m_vData[ i ].m_sColorP.c_str() , osg::Vec3( 1,1,0 ) );
		m_vData[ i ].m_unfColorS = new osg::Uniform( m_vData[ i ].m_sColorS.c_str() , osg::Vec3( 0.5,0.25,0 ) );
		m_vData[ i ].m_unfKofScale = new osg::Uniform( m_vData[ i ].m_sKofScale.c_str() , 256.0f );
		m_vData[ i ].m_unfDist = new osg::Uniform( m_vData[ i ].m_sDist.c_str() , 16384.0f * DIST_SCALE );

		//добавить геометрию в i'ый узел
		AddGeometry( i );

		//настроить параметры необходимые в шейдере
		SetupShaderParam( i );

		m_rootNode->addChild( m_vData[ i ].m_Geode.get() );
	}
}

void DynamicGroupLevel16384Node::ResetRootNode()
{
	//удалить всех потомков корневого узла
	m_iCount = 0;
	m_rootNode->removeChildren( 0 , m_rootNode->getNumChildren() );
}

void DynamicGroupLevel16384Node::AddGeometry( int i )
{
	//добавить геометрию в i'ый узел

	//создать объект для хранения в нем геометрии
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	//создать массив вершин
	geom->setVertexArray( CreateVertexArray( 0 , 0 , 64 + 32 , 16384 ).get() );

	std::vector< unsigned short > m_vIndex;

	//заполнить вектор индексами
	FillIndexVector( m_vIndex , 64 + 32 );

	geom->addPrimitiveSet( new osg::DrawElementsUShort(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() / GEOM_DIV , &m_vIndex[ 0 ] ) );

	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	geom->setInitialBound( bbox );

	//добавить рисуемую геометрию
	m_vData[ i ].m_Geode->addDrawable( geom.get() );
}

void DynamicGroupLevel16384Node::SetupShaderParam( int i )
{
	//настроить параметры необходимые в шейдере

	//формирование сцены с шейдером
	osg::StateSet* ss = m_vData[ i ].m_Geode->getOrCreateStateSet();

	//добавление uniform'а для задания смещения патча
	ss->addUniform( m_vData[ i ].m_unfOffset.get() );
	ss->addUniform( m_vData[ i ].m_unfColorP.get() );
	ss->addUniform( m_vData[ i ].m_unfColorS.get() );
	ss->addUniform( m_vData[ i ].m_unfKofScale.get() );
	ss->addUniform( m_vData[ i ].m_unfDist.get() );
}

osg::ref_ptr<osg::Vec4Array> DynamicGroupLevel16384Node::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{

	//создать массив вершин
	osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;

	//kof = 256.0f
	float kof = (float)scaleC / (float)( sizeC - 32 );
	kof = 1.0;

	//номер ячейки в которой будет сдвиг
	int iQuad = ( sizeC - 32 ) / 32 + 1;

	//смещение по Y
	int iY = 0;

	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		//момент когда надо сдвигать на 1 по Y
		int shift = iQuad * ( iY + 1 );

		//если i совпадает с iHalf то сместиться на 1 вниз
		if ( i == shift )
			++iY;

		//смещение по X
		int iX = 0;
		for (int j = 0 ; j < sizeC ; ++j )
		{
			//момент когда надо сдвигать на 1 по Y
			int shift = iQuad * ( iX + 1 );

			//если j совпадает с iHalf то сместиться на 1 в лево
			if ( j == shift )
				++iX;

			v->push_back( osg::Vec4( x + ( j - iX ) * kof , y + ( i - iY ) * kof , iX , iY ) );
		}
	}

	return v.get();
}

void DynamicGroupLevel16384Node::FillIndexVector( std::vector< unsigned short > &m_vIndex , int sizeC )
{
	//заполнить вектор индексами
	//заполнить вектор индексами
	m_vIndex.push_back( 0 );
	m_vIndex.push_back( sizeC );
	int count = sizeC - 1;
	int ind = 0;
	while( count > 0 )
	{
		for( int i = 0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + 1 );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + 1 );
		}
		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
		count--;

		for( int i = 0 ; i< count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
		}

		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );

		for( int i = 0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - 1 );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - 1 );
		}

		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
		count--;

		for( int i=0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
		}
		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
	}
}

void DynamicGroupLevel16384Node::AddPatch( float x , float y )
{
	//добавить патч геометрии из буффера в корневой узел

	//обновить данные в uniform'e
	m_vData[ m_iCount ].m_unfOffset->set( osg::Vec3( x , y , 0.0f ) );

	//добавить очередной узел из буффера
	m_rootNode->addChild( m_vData[ m_iCount ].m_Geode.get() );

	++m_iCount;
}

void DynamicGroupLevel16384Node::PrintSize()
{
	//вывести количество узлов для отрисовки
	std::cout << m_rootNode->getNumChildren() << " ";
}