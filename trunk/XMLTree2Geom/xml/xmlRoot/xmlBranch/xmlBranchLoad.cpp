#include "xmlBranchLoad.h"

#include "xmlBranchNames.h"

xmlBranchLoad::xmlBranchLoad() : m_pData( NULL )
{

}

xmlBranchLoad::~xmlBranchLoad()
{

}

void xmlBranchLoad::ParseXml( ticpp::Node* pNode , binBranch *_data )
{
	//������ xml � ���������� �������� ������
	m_pData = _data;

	//������� � ���� branch
	DecodeSettings( pNode );
}

void xmlBranchLoad::DecodeSettings( ticpp::Node* pNode )
{
	//������� � ���� branch
	ticpp::Element* pBranch = pNode->FirstChildElement( m_BranchNames.m_sBranch ,false );
	if ( pBranch )
	{
		//������� ������� � ������ ��������
		pBranch->GetAttribute( m_BranchNames.m_sTexture , &m_pData->m_sTexture , false );

		//������� � ���� � LOD'���
		ticpp::Element* pLODs = pBranch->FirstChildElement( m_BranchNames.m_sLODs ,false );
		if ( pLODs )
		{
			//������� ���������� LOD'��
			int iSize = 0;
			pLODs->GetAttribute( m_BranchNames.m_sNum , &iSize , false );
			if ( iSize > 0 )
			{
				//�������� ������
				m_pData->m_vBranch.resize( iSize );

				//������� ������ LOD'��
				DecodeLODs( pLODs );
			}
		}
	}
}

void xmlBranchLoad::DecodeLODs( ticpp::Element* pLODs )
{
	//������� ������ LOD'��
	try
	{
		ticpp::Iterator< ticpp::Element > pLOD( m_BranchNames.m_sLOD );
		for ( pLOD = pLOD.begin( pLODs ); pLOD != pLOD.end(); pLOD++ )
		{
			int iNum = -1;
			pLOD->GetAttribute( m_BranchNames.m_sNum , &iNum );
			pLOD->GetAttribute( m_BranchNames.m_sAlfaTest , &m_pData->m_vBranch[ iNum ].m_fAlfa );

			//������� ���������� �����
			DecodePoint( pLOD->FirstChildElement( m_BranchNames.m_sVertexs ) , iNum );
		}

	}
	catch( ticpp::Exception& ex )
	{
		//If any function has an error, execution will enter here.
		//	Report the error
		std::cout << ex.what();
	}
}

void xmlBranchLoad::DecodePoint( ticpp::Element* pVertex , int i )
{
	//������� ���������� �����
	int iNum = 0;
	pVertex->GetAttribute( m_BranchNames.m_sNum , &iNum );
	m_pData->m_vBranch[ i ].m_vVertex.resize( iNum * 3 );
	ticpp::Iterator< ticpp::Element > pPoint( m_BranchNames.m_sPoint );
	for ( pPoint = pPoint.begin( pVertex ); pPoint != pPoint.end(); pPoint++ )
	{
		float fX = 0.0f , fY = 0.0f , fZ = 0.0f;		//���������� �������
		float fnX = 0.0f , fnY = 0.0f , fnZ = 0.0f;		//������� �������
		float fS = 0.0f , fT = 0.0f;					//���������� ����������

		//��������� ���������� �������
		pPoint->GetAttribute( m_BranchNames.m_sX , &fX );
		pPoint->GetAttribute( m_BranchNames.m_sY , &fY );
		pPoint->GetAttribute( m_BranchNames.m_sZ , &fZ );

		//�������
		pPoint->GetAttribute( m_BranchNames.m_snX , &fnX );
		pPoint->GetAttribute( m_BranchNames.m_snY , &fnY );
		pPoint->GetAttribute( m_BranchNames.m_snZ , &fnZ );
	}
}