#include "DynamicGroupSize.h"

#include "DynamicGroupUpdateCallback.h"

#include <osg/Geometry>

#define  NUM_INSTANCE 16

DynamicGroupSize::DynamicGroupSize()
{
	//резервируем память для NUM_INSTANCE элементов
	m_vecGeode.reserve( NUM_INSTANCE );

	//создать главный узел
	m_rootNode = new osg::Group;

	//динамический узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );

	//инициализировать корневой узел
	InitNode();

	m_rootNode->setUpdateCallback( new DynamicGroupUpdateCallback( m_vecGeode ) );
}

DynamicGroupSize::~DynamicGroupSize()
{

}

void DynamicGroupSize::InitNode()
{
//инициализировать корневой узел
	for ( int step = 0 ; step < NUM_INSTANCE ; ++step )
	{
		// Create an object to store geometry in.
		osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

		// Create an array of four vertices.
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
		geom->setVertexArray( v.get() );


//////////////////////////////////////////////////////////////////////////
		std::vector< unsigned int > m_vIndex;

		int sizeC=17;
		//Заполнение массива points
		for (int i = 0 ; i < sizeC ; ++i )
			for (int j = 0 ; j < sizeC ; ++j )
			{
				v->push_back( osg::Vec3( j + step * sizeC + sizeC, 0 , i) );
			}

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
//////////////////////////////////////////////////////////////////////////
		geom->addPrimitiveSet( new osg::DrawElementsUInt(
			osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size(), &m_vIndex[ 0 ] ) );

		// Add the Geometry (Drawable) to a Geode and
		// return the Geode.
		osg::ref_ptr< osg::Geode > geode = new osg::Geode;
		geode->addDrawable( geom.get() );

		//запоминаем geode
		m_vecGeode.push_back( geode );

		m_rootNode->addChild( geode.get() );
	}
}