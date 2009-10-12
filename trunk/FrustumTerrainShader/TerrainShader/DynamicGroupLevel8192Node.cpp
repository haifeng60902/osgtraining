#include "DynamicGroupLevel8192Node.h"

#include <osg/Geometry>

#include <iostream>

DynamicGroupLevel8192Node::DynamicGroupLevel8192Node() : m_iCount( 0 )
{
	//��������������� ������ ��� 128 �����
	m_vData.resize( 128 );

	//������ �����
	m_rootNode = new osg::Group;

	//���������������� ��������� ������ ������ �����������
	InitGeodes();

	//���� ����������� ������ ���������� ��������
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

void DynamicGroupLevel8192Node::InitGeodes()
{
	//���������������� ��������� ������ ������ �����������

	for ( int i = 0 ; i < m_vData.size() ; ++i )
	{
		//�������� ���� ���������
		m_vData[ i ].m_Geode = new osg::Geode;

		//�������� uniform
		m_vData[ i ].m_unfOffset = new osg::Uniform( m_vData[ i ].m_sOffset.c_str() , osg::Vec3( 0,0,0) );
		m_vData[ i ].m_unfColorP = new osg::Uniform( m_vData[ i ].m_sColorP.c_str() , osg::Vec3( 0,0,0 ) );
		m_vData[ i ].m_unfColorS = new osg::Uniform( m_vData[ i ].m_sColorS.c_str() , osg::Vec3( 1,1,0 ) );
		m_vData[ i ].m_unfKofScale = new osg::Uniform( m_vData[ i ].m_sKofScale.c_str() , 128.0f );
		m_vData[ i ].m_unfDist = new osg::Uniform( m_vData[ i ].m_sDist.c_str() , 8192.0f * DIST_SCALE );
		m_vData[ i ].m_unfTexCoordAdd = new osg::Uniform( m_vData[ i ].m_sTexCoordAdd.c_str() , 2.0f );
		m_vData[ i ].m_unfTexCoordScale = new osg::Uniform( m_vData[ i ].m_sTexCoordScale.c_str() , 128.0f );

		//�������� ��������� � i'�� ����
		AddGeometry( i );

		//��������� ��������� ����������� � �������
		SetupShaderParam( i );

		m_rootNode->addChild( m_vData[ i ].m_Geode.get() );
	}
}

void DynamicGroupLevel8192Node::ResetRootNode()
{
	//������� ���� �������� ��������� ����
	m_iCount = 0;
	m_rootNode->removeChildren( 0 , m_rootNode->getNumChildren() );
}

void DynamicGroupLevel8192Node::AddGeometry( int i )
{
	//�������� ��������� � i'�� ����

	//������� ������ ��� �������� � ��� ���������
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	//������� ������ ������
	geom->setVertexArray( CreateVertexArray( 0 , 0 , 64 + 16 , 8192 ).get() );

	std::vector< unsigned short > m_vIndex;

	//��������� ������ ���������
	FillIndexVector( m_vIndex , 64 + 16 );

	geom->addPrimitiveSet( new osg::DrawElementsUShort(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size() / GEOM_DIV , &m_vIndex[ 0 ] ) );

	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	geom->setInitialBound( bbox );

	//�������� �������� ���������
	m_vData[ i ].m_Geode->addDrawable( geom.get() );
}

void DynamicGroupLevel8192Node::SetupShaderParam( int i )
{
	//��������� ��������� ����������� � �������

	//������������ ����� � ��������
	osg::StateSet* ss = m_vData[ i ].m_Geode->getOrCreateStateSet();

	//���������� uniform'� ��� ������� �������� �����
	ss->addUniform( m_vData[ i ].m_unfOffset.get() );
	ss->addUniform( m_vData[ i ].m_unfColorP.get() );
	ss->addUniform( m_vData[ i ].m_unfColorS.get() );
	ss->addUniform( m_vData[ i ].m_unfKofScale.get() );
	ss->addUniform( m_vData[ i ].m_unfDist.get() );
	ss->addUniform( m_vData[ i ].m_unfTexCoordAdd.get() );
	ss->addUniform( m_vData[ i ].m_unfTexCoordScale.get() );
}

osg::ref_ptr<osg::Vec4Array> DynamicGroupLevel8192Node::CreateVertexArray( int x , int y , int sizeC , int scaleC )
{

	//������� ������ ������
	osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;

	//kof = 128.0f
	float kof = (float)scaleC / (float)( sizeC - 16 );
	kof = 1.0;

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

			v->push_back( osg::Vec4( x + ( j - iX ) * kof , y + ( i - iY ) * kof , iX , iY ) );
		}
	}

	return v.get();
}

void DynamicGroupLevel8192Node::FillIndexVector( std::vector< unsigned short > &m_vIndex , int sizeC )
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

void DynamicGroupLevel8192Node::AddPatch( float x , float y )
{
	//�������� ���� ��������� �� ������� � �������� ����

	//�������� ������ � uniform'e
	m_vData[ m_iCount ].m_unfOffset->set( osg::Vec3( x , y , 0.0f ) );

	//�������� ��������� ���� �� �������
	m_rootNode->addChild( m_vData[ m_iCount ].m_Geode.get() );

	++m_iCount;
}

void DynamicGroupLevel8192Node::PrintSize()
{
	//������� ���������� ����� ��� ���������
	std::cout << m_rootNode->getNumChildren() << " ";
}