#include "DynamicGroupLevel0512Node.h"

#include <osg/Geometry>

#include <iostream>

DynamicGroupLevel0512Node::DynamicGroupLevel0512Node() : m_iCount( 0 )
{
	//��������������� ������ ��� 32 �����
	m_vData.resize( 32 );

	//������ �����
	m_rootNode = new osg::Group;

	//���������������� ��������� ������ ������ �����������
	InitGeodes();

	//���� ����������� ������ ���������� ��������
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

void DynamicGroupLevel0512Node::InitGeodes()
{
	//���������������� ��������� ������ ������ �����������

	for ( int i = 0 ; i < m_vData.size() ; ++i )
	{
		//�������� ���� ���������
		m_vData[ i ].m_Geode = new osg::Geode;

		//�������� uniform
		m_vData[ i ].m_Uniform = new osg::Uniform( "posOffset" , osg::Vec3( 0,0,0) );

		//�������� ��������� � i'�� ����
		AddGeometry( i );

		//��������� ��������� ����������� � �������
		SetupShaderParam( i );

		m_rootNode->addChild( m_vData[ i ].m_Geode.get() );
	}
}

void DynamicGroupLevel0512Node::ResetRootNode()
{
	//������� ���� �������� ��������� ����
	m_iCount = 0;
	m_rootNode->removeChildren( 0 , m_rootNode->getNumChildren() );
}

void DynamicGroupLevel0512Node::AddGeometry( int i )
{
	//�������� ��������� � i'�� ����

	//������� ������ ��� �������� � ��� ���������
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	//������� ������ ������
	geom->setVertexArray( CreateVertexArray( 0 , 0 , 65 , 512 ).get() );

	std::vector< unsigned int > m_vIndex;

	//��������� ������ ���������
	FillIndexVector( m_vIndex , 65 );

	geom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() , &m_vIndex[ 0 ] ) );

	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	geom->setInitialBound( bbox );

	//�������� �������� ���������
	m_vData[ i ].m_Geode->addDrawable( geom.get() );
}

void DynamicGroupLevel0512Node::SetupShaderParam( int i )
{
	//��������� ��������� ����������� � �������

	//������������ ����� � ��������
	osg::StateSet* ss = m_vData[ i ].m_Geode->getOrCreateStateSet();

	//���������� uniform'� ��� ������� �������� �����
	ss->addUniform( m_vData[ i ].m_Uniform.get() );
}

osg::ref_ptr<osg::Vec3Array> DynamicGroupLevel0512Node::CreateVertexArray( int x , int y , int sizeC , int scaleC )
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

void DynamicGroupLevel0512Node::FillIndexVector( std::vector< unsigned int > &m_vIndex , int sizeC )
{
	//��������� ������ ���������
	//��������� ������ ���������
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

void DynamicGroupLevel0512Node::AddPatch( float x , float y )
{
	//�������� ���� ��������� �� ������� � �������� ����
	
	//�������� ������ � uniform'e
	m_vData[ m_iCount ].m_Uniform->set( osg::Vec3( x , y , 0.0f ) );

	//�������� ��������� ���� �� �������
	m_rootNode->addChild( m_vData[ m_iCount ].m_Geode.get() );

	++m_iCount;
}

void DynamicGroupLevel0512Node::PrintSize()
{
	//������� ���������� ����� ��� ���������
	std::cout << m_rootNode->getNumChildren() << " ";
}