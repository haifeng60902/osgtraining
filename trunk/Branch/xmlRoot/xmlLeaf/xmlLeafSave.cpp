#include "xmlLeafSave.h"

#include "../xmlRoot.h"
#include "xmlLeafNames.h"

xmlLeafSave::xmlLeafSave()
{

}

xmlLeafSave::~xmlLeafSave()
{

}

TiXmlElement* xmlLeafSave::GetXmlData()
{
	//�������� xml ��� � ��������������� �������

	//�������� ������ �� ������ �����
	dataLeaf &_data = xmlRoot::Instance().GetDataLeaf();

	//��������� �������� ���� ������
	TiXmlElement *pLeaf = NULL;
	pLeaf = new TiXmlElement( m_LeafNames.m_sLeaf.c_str() );

	//�������� ����� �����
	pLeaf->SetDoubleAttribute( m_LeafNames.m_sAlfaTest.c_str() , _data.m_fAlphaTestValue );

	//��������� ������� � ���������
	FillTextures( _data  , pLeaf );

	//��������� ������� � �����������
	FillVertex( _data  ,  pLeaf );

	//��������� ������� � �����
	FillWind( pLeaf );

	return pLeaf;
}

void xmlLeafSave::FillTextures( const dataLeaf &_data  , TiXmlElement* root )
{
	//��������� ������� � ���������

	//������� ������ ��� �������
	TiXmlElement *pTextures = NULL;
	pTextures = new TiXmlElement( m_LeafNames.m_sTextures.c_str() );

	//���������� �������
	pTextures->SetAttribute( m_LeafNames.m_sNum.c_str() , _data.m_vTextures.size() );

	for ( int i = 0 ; i < _data.m_vTextures.size() ; ++i )
	{
		TiXmlElement *pTexture = NULL;
		pTexture = new TiXmlElement( m_LeafNames.m_sTexture.c_str() );

		//���������� �������
		pTexture->SetAttribute( m_LeafNames.m_sVal.c_str() , _data.m_vTextures[ i ].c_str() );

		pTextures->LinkEndChild( pTexture );
	}

	root->LinkEndChild( pTextures );
}

void xmlLeafSave::FillVertex( const dataLeaf &_data  , TiXmlElement* root )
{
	//������� ������ ��� ������
	TiXmlElement *pVertexs = NULL;
	pVertexs = new TiXmlElement( m_LeafNames.m_sVertexs.c_str() );

	//���������� ������
	pVertexs->SetAttribute( m_LeafNames.m_sNum.c_str() , _data.m_vCoords.size() / 3 );

	for ( int i = 0; i < _data.m_vCoords.size() / 3; ++i )
	{
		//�������� ���� ��������� �����
		TiXmlElement *pPoint = new TiXmlElement( m_LeafNames.m_sPoint.c_str() );

		//�������� �����
		pPoint->SetDoubleAttribute( m_LeafNames.m_sX.c_str() , _data.m_vCoords[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sY.c_str() , _data.m_vCoords[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sZ.c_str() , _data.m_vCoords[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_LeafNames.m_snX.c_str() , _data.m_vNormals[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_snY.c_str() , _data.m_vNormals[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_snZ.c_str() , _data.m_vNormals[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_LeafNames.m_sS0.c_str() , _data.m_vTexCoords0[ i * 4 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sT0.c_str() , _data.m_vTexCoords0[ i * 4 + 1 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sP0.c_str() , _data.m_vTexCoords0[ i * 4 + 2 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sQ0.c_str() , _data.m_vTexCoords0[ i * 4 + 3 ] );

		pPoint->SetDoubleAttribute( m_LeafNames.m_sS1.c_str() , _data.m_vTexCoords1[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sT1.c_str() , _data.m_vTexCoords1[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_LeafNames.m_sP1.c_str() , _data.m_vTexCoords1[ i * 3 + 2 ] );

		pVertexs->LinkEndChild( pPoint );
	}

	root->LinkEndChild( pVertexs );
}

void xmlLeafSave::FillWind( TiXmlElement* root )
{
	//��������� ������� � �����

	//������� ������ ��� �����
	TiXmlElement *pWind = NULL;
	pWind = new TiXmlElement( m_LeafNames.m_sWind.c_str() );

	//������� �������� ������ ��� Y
	pWind->SetAttribute( m_LeafNames.m_sFreqY.c_str() , 0 );

	//��������� �������� ������ ��� Y
	pWind->SetAttribute( m_LeafNames.m_sAmplY.c_str() , 0 );

	//������� �������� ������ ��� Z
	pWind->SetAttribute( m_LeafNames.m_sFreqZ.c_str() , 0 );

	//��������� �������� ������ ��� Z
	pWind->SetAttribute( m_LeafNames.m_sAmplZ.c_str() , 0 );

	root->LinkEndChild( pWind );
}