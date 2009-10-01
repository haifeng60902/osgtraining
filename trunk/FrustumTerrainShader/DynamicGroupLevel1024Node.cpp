#include "DynamicGroupLevel1024Node.h"

#include <osg/Geometry>

#include <iostream>

DynamicGroupLevel1024Node::DynamicGroupLevel1024Node() : m_iCount( 0 )
{
	//зарезервировать память для 128 узлов
	m_vData.resize( 128 );

	//группа узлов
	m_rootNode = new osg::Group;

	//инициализировать геометрию патчей земной поверхности
	InitGeodes();

	//узел динамически меняет количество потомков
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

void DynamicGroupLevel1024Node::InitGeodes()
{
	//инициализировать геометрию патчей земной поверхности

	for ( int i = 0 ; i < m_vData.size() ; ++i )
	{
		//добавить узел геометрии
		m_vData[ i ].m_Geode = new osg::Geode;

		//добавить uniform
		m_vData[ i ].m_unfOffset = new osg::Uniform( m_vData[ i ].m_sOffset.c_str() , osg::Vec3( 0,0,0) );
		m_vData[ i ].m_unfColorP = new osg::Uniform( m_vData[ i ].m_sColorP.c_str() , osg::Vec3( 0,0,1 ) );
		m_vData[ i ].m_unfColorS = new osg::Uniform( m_vData[ i ].m_sColorS.c_str() , osg::Vec3( 0,1,0 ) );
		m_vData[ i ].m_unfKofScale = new osg::Uniform( m_vData[ i ].m_sKofScale.c_str() , 16.0f );
		m_vData[ i ].m_unfDist = new osg::Uniform( m_vData[ i ].m_sDist.c_str() , 1024.0f * DIST_SCALE );
		m_vData[ i ].m_unfTexCoordAdd = new osg::Uniform( m_vData[ i ].m_sTexCoordAdd.c_str() , 2.0f );
		m_vData[ i ].m_unfTexCoordScale = new osg::Uniform( m_vData[ i ].m_sTexCoordScale.c_str() , 64.0f );

		//добавить геометрию в i'ый узел
		AddGeometry( i );

		//настроить параметры необходимые в шейдере
		SetupShaderParam( i );

		m_rootNode->addChild( m_vData[ i ].m_Geode.get() );
	}
}

void DynamicGroupLevel1024Node::ResetRootNode()
{
	//удалить всех потомков корневого узла
	m_iCount = 0;
	m_rootNode->removeChildren( 0 , m_rootNode->getNumChildren() );
}

void DynamicGroupLevel1024Node::AddGeometry( int i )
{
	//добавить геометрию в i'ый узел

	//создать объект для хранения в нем геометрии
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	//создать массив вершин
	geom->setVertexArray( CreateVertexArray( 0 , 0 , 66 , 1024 ).get() );

	std::vector< unsigned short > m_vIndex;

	//заполнить вектор индексами
	FillIndexVector( m_vIndex , 66 );

	geom->addPrimitiveSet( new osg::DrawElementsUShort(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() / GEOM_DIV , &m_vIndex[ 0 ] ) );

	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	geom->setInitialBound( bbox );

	//добавить рисуемую геометрию
	m_vData[ i ].m_Geode->addDrawable( geom.get() );
}

void DynamicGroupLevel1024Node::SetupShaderParam( int i )
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
	ss->addUniform( m_vData[ i ].m_unfTexCoordAdd.get() );
	ss->addUniform( m_vData[ i ].m_unfTexCoordScale.get() );
}

osg::ref_ptr<osg::Vec4Array> DynamicGroupLevel1024Node::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{
	//создать массив вершин
	osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;

	//kof = 16.0f
	float kof = (float)scaleC / (float)( sizeC - 2 );
	kof = 1.0;

	//номер ячейки в которой будет сдвиг
	int iHalf = ( sizeC - 2 ) / 2 + 1;

	//смещение по Y
	float fY = 0;

	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
	{
		//если i совпадает с iHalf то сместиться на 1 вниз
		if ( i == iHalf )
			++fY;

		//смещение по X
		float fX = 0;
		for (int j = 0 ; j < sizeC ; ++j )
		{
			//если j совпадает с iHalf то сместиться на 1 в лево
			if ( j == iHalf )
				++fX;

			v->push_back( osg::Vec4( x + ( j - fX ) * kof , y + ( i - fY ) * kof , fX , fY ) );
		}
	}

	return v.get();
}

void DynamicGroupLevel1024Node::FillIndexVector( std::vector< unsigned short > &m_vIndex , int sizeC )
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

void DynamicGroupLevel1024Node::AddPatch( float x , float y )
{
	//добавить патч геометрии из буффера в корневой узел

	//обновить данные в uniform'e
	m_vData[ m_iCount ].m_unfOffset->set( osg::Vec3( x , y , 0.0f ) );

	//добавить очередной узел из буффера
	m_rootNode->addChild( m_vData[ m_iCount ].m_Geode.get() );

	++m_iCount;
}

void DynamicGroupLevel1024Node::PrintSize()
{
	//вывести количество узлов для отрисовки
	std::cout << m_rootNode->getNumChildren() << " ";
}