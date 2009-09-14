#include "xmlBranchSave.h"

#include "../xmlRoot.h"
#include "xmlBranchNames.h"

xmlBranchSave::xmlBranchSave()
{

}

xmlBranchSave::~xmlBranchSave()
{

}

TiXmlElement* xmlBranchSave::GetXmlData()
{
	//�������� xml ��� � ��������������� �������

	//�������� ������ �� ������ ������
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	//��������� �������� ���� ������
	TiXmlElement *pBranch = NULL;
	pBranch = new TiXmlElement( m_BranchNames.m_sBranch.c_str() );

	//�������� ����� �����
	pBranch->SetAttribute( m_BranchNames.m_sTexture.c_str() , _data.m_sTexture.c_str() );

	//������������ ������� LOD'��
	FillLODs( _data  , pBranch );

	return pBranch;
}

void xmlBranchSave::FillLODs( const dataBranch &_data  , TiXmlElement* root )
{
	//������������ ������� LOD'��

	//������� ������ ��� ������
	TiXmlElement *pLods = NULL;
	pLods = new TiXmlElement( m_BranchNames.m_sLODs.c_str() );

	//���������� LOD's
	pLods->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_vLOD.size() );

	for( int i = 0 ; i < _data.m_vLOD.size() ; ++i )
	{
		//������� ������ ��� ������
		TiXmlElement *pLod = NULL;
		pLod = new TiXmlElement( m_BranchNames.m_sLOD.c_str() );

		//����� LOD's
		pLod->SetAttribute( m_BranchNames.m_sNum.c_str() , i );

		//����� LOD's
		pLod->SetDoubleAttribute( m_BranchNames.m_sAlfaTest.c_str() , _data .m_vLOD[ i ].m_fAlphaTestValue );

		//��������� ������� � �����������
		FillVertex( _data .m_vLOD[ i ] ,  pLod );

		//��������� ���������
		FillIndexes( _data .m_vLOD[ i ]  ,  pLod );

		pLods->LinkEndChild( pLod );
	}

	root->LinkEndChild( pLods );
}

void xmlBranchSave::FillVertex( const dataLOD &_data  , TiXmlElement* root )
{
	//��������� ��� ������� �����

	//������� ������ ��� ������
	TiXmlElement *pVertexs = NULL;
	pVertexs = new TiXmlElement( m_BranchNames.m_sVertexs.c_str() );

	//���������� ������
	pVertexs->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_vCoords.size() / 3 );

	for ( int i = 0; i < _data.m_vCoords.size() / 3; ++i )
	{
		//�������� ���� ��������� �����
		TiXmlElement *pPoint = new TiXmlElement( m_BranchNames.m_sPoint.c_str() );

		//�������� �����
		pPoint->SetDoubleAttribute( m_BranchNames.m_sX.c_str() , _data.m_vCoords[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_sY.c_str() , _data.m_vCoords[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_sZ.c_str() , _data.m_vCoords[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_BranchNames.m_snX.c_str() , _data.m_vNormals[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_snY.c_str() , _data.m_vNormals[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_snZ.c_str() , _data.m_vNormals[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_BranchNames.m_sS.c_str() , _data.m_vTexCoords0[ i * 4 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_sT.c_str() , _data.m_vTexCoords0[ i * 4 + 1 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_sP.c_str() , _data.m_vTexCoords0[ i * 4 + 2 ] );
		pPoint->SetDoubleAttribute( m_BranchNames.m_sQ.c_str() , _data.m_vTexCoords0[ i * 4 + 3 ] );

		pVertexs->LinkEndChild( pPoint );
	}

	root->LinkEndChild( pVertexs );
}

void xmlBranchSave::FillIndexes( const dataLOD &_data  , TiXmlElement* root )
{
	//��������� ���������

	//������� ������ ��� ���������� ������� ����
	TiXmlElement *pStrips = NULL;
	pStrips = new TiXmlElement( m_BranchNames.m_sStrips.c_str() );

	//���������� TRIANGLE_STRIP
	pStrips->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_Strips.size() );

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		TiXmlElement *pStrip = NULL;
		pStrip = new TiXmlElement( m_BranchNames.m_sStrip.c_str() );

		//���������� ���������
		pStrip->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_Strips[ i ].size() );

		for ( int j = 0 ; j < _data.m_Strips[ i ].size() ; ++ j )
		{
			TiXmlElement *pInd = NULL;
			pInd = new TiXmlElement( m_BranchNames.m_sInd.c_str() );

			//���������� ���������
			pInd->SetAttribute( m_BranchNames.m_sVal.c_str() , _data.m_Strips[ i ][ j ] );

			pStrip->LinkEndChild( pInd );
		}

		pStrips->LinkEndChild( pStrip );
	}

	root->LinkEndChild( pStrips );
}