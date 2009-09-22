#include "DynamicGroupUpdateCallback.h"

#include "dataPatch.h"

#include "GeometryPatch.h"
#include "GeometryTexturePatch.h"

#include <osgDB/ReadFile>

#include <iostream>
#include <fstream>

int iCount = 0;

DynamicGroupUpdateCallback::DynamicGroupUpdateCallback() : m_dAdd( 1.0 )
, m_dScale( 30.0 )
{
	// ��������� �����������
	m_ImageIndex = osgDB::readImageFile( "index.bmp" );
}

DynamicGroupUpdateCallback::~DynamicGroupUpdateCallback()
{

}

void DynamicGroupUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//������������ ������ ������ � ������� ������
	m_VisiblePatchArray.Update();

	//�������� ������������ �� �����
//	UpdateKof();

	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group )
	{
		//������� ������ �� ������ ������� ������
		const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

		if ( !data_vis.empty() )
		{
			//std::cout << data_vis.size() << "-" << FindMax() << " ";

			//�������� ���� �����
			group->removeChildren( 0 , group->getNumChildren() );

			//��������� ��� ������� ����
			for( int i = 0 ; i < data_vis.size() ; ++i )
			{
				//������������ ���������
				//GeometryPatch patch( data_vis[ i ].m_iX , 
				//	data_vis[ i ].m_iY , 65 , 
				//	data_vis[ i ].m_iSize );

				GeometryTexturePatch patch( data_vis[ i ].m_iX , 
					data_vis[ i ].m_iY , 65 , 
					data_vis[ i ].m_iSize , m_ImageIndex.get()
					, m_dAdd , m_dScale );

				osg::ref_ptr< osg::Geode > geode = new osg::Geode;
				geode->addDrawable( patch.GetGeometry().get() );

				//�������� ��������� � �����
				group->addChild( geode.get() );
			}
		}
	}
}

int DynamicGroupUpdateCallback::FindMax()
{
	//����� ������������� ������� �����

	//������� ������ �� ������ ������� ������
	const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

	int iMax = data_vis[ 0 ].m_iSize;

	for ( int i = 1 ; i < data_vis.size() ; ++i )
		if ( data_vis[ i ].m_iSize > iMax)
			iMax = data_vis[ i ].m_iSize;

	if ( iMax > 32768 )
	{
		int a = 1;
	}

	return iMax;
}

void DynamicGroupUpdateCallback::UpdateKof()
{
	//�������� ������������ �� �����

	if ( !( iCount % 60 ) )
	{
		// ����� ��� ������ �����
		std::ifstream m_in;

		m_in.open( "in.txt", std::ios::in);

		m_in >> m_dAdd >> m_dScale;

		m_in.close();

	}

	++iCount;
}