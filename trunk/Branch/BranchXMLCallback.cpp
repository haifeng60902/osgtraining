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
		//�������� ���������� ��������
		ChangeNumIndex();

		return;
	}

	//�������� ��������� � osg::Geode
	osg::Geode *geode = dynamic_cast< osg::Geode* >( node );
	if ( geode )
	{
		//�������� ��������� ���� osg::Geometry
		osg::Geometry *geom = dynamic_cast< osg::Geometry* >( geode->getDrawable( 0 ) );

		if ( geom )
		{
			m_pDE = dynamic_cast< osg::DrawElementsUShort* >( geom->getPrimitiveSet( 0 ) );

			if ( m_pDE )
			{
				//��� ������ ������ ���������� ��������� �� ����� ��������� ��������� � �� ����������
				m_iMaxInd = m_pDE->getNumIndices();

				//�������� ������� � �����
				for ( int i = 0 ; i < m_iMaxInd ; ++i )
					m_usV.push_back( m_pDE->at( i ) );
			}
		}
	}
}

void BranchXMLCallback::ChangeNumIndex()
{
	//�������� ���������� ��������
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