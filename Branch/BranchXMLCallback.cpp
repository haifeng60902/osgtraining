#include "BranchXMLCallback.h"

#include <osg/Geometry>
#include <osg/Geode>

BranchXMLCallback::BranchXMLCallback() : m_iMaxInd( -1 )
	, m_pDE( NULL )
{

}

BranchXMLCallback::~BranchXMLCallback()
{

}

void BranchXMLCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{

	if ( ( m_pDE ) && ( m_iMaxInd > 0 ) )
	{
		//изменить количество индексов
		ChangeNumIndex();

		return;
	}

	//привести указатель к osg::Geode
	osg::Geode *geode = dynamic_cast< osg::Geode* >( node );
	if ( geode )
	{
		//привести указатель одну osg::Geometry
		osg::Geometry *geom = dynamic_cast< osg::Geometry* >( geode->getDrawable( 0 ) );

		if ( geom )
		{
			m_pDE = dynamic_cast< osg::DrawElementsUShort* >( geom->getPrimitiveSet( 0 ) );

			if ( m_pDE )
			{
				//при первом вызове запоминаем указатель на класс отрисовки геометрии и ее количество
				m_iMaxInd = m_pDE->getNumIndices();

				//копируем индексы в буфер
				for ( int i = 0 ; i < m_iMaxInd ; ++i )
					m_usV.push_back( m_pDE->at( i ) );
			}
		}
	}
}

void BranchXMLCallback::ChangeNumIndex()
{
	//изменить количество индексов
	static int sign = -1;
	static int num = m_iMaxInd;

	num += sign;
	if ( num < 3 )
		sign = 1;
	else
		if ( num > m_iMaxInd - 1 )
			sign = -1;
	
	m_pDE->resize( num );

	for ( int i = 0 ; i < num ; ++i )
		m_pDE->at( i ) = m_usV[ i ];
}