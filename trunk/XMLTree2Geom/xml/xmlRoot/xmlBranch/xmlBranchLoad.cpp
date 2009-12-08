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

			//������� �������
			DecodeStrips( pLOD->FirstChildElement( m_BranchNames.m_sStrips ) , iNum );
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
	ticpp::Iterator< ticpp::Element > pPoint( m_BranchNames.m_sPoint );
	for ( pPoint = pPoint.begin( pVertex ); pPoint != pPoint.end(); pPoint++ )
	{
		//������� ���������� �������
		DecodeVertex( pPoint , &m_pData->m_vBranch[ i ].m_vVertex );

		//������� ���������� �������
		DecodeNormal( pPoint , &m_pData->m_vBranch[ i ].m_vNormal );

		//������� ���������� ����������
		DecodeTexCoord( pPoint , &m_pData->m_vBranch[ i ].m_vTexCoord );
	}
}

void xmlBranchLoad::DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pVertex )
{
	//������� ���������� �������
	float fX = 0.0f , fY = 0.0f , fZ = 0.0f;		//���������� �������

	//��������� ���������� �������
	pPoint->GetAttribute( m_BranchNames.m_sX , &fX );
	pPoint->GetAttribute( m_BranchNames.m_sY , &fY );
	pPoint->GetAttribute( m_BranchNames.m_sZ , &fZ );

	//���������� � �������
	pVertex->push_back( fX );
	pVertex->push_back( fY );
	pVertex->push_back( fZ );
}

void xmlBranchLoad::DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pNormal )
{
	//������� ���������� �������
	float fnX = 0.0f , fnY = 0.0f , fnZ = 0.0f;		//������� �������

	//�������
	pPoint->GetAttribute( m_BranchNames.m_snX , &fnX );
	pPoint->GetAttribute( m_BranchNames.m_snY , &fnY );
	pPoint->GetAttribute( m_BranchNames.m_snZ , &fnZ );

	//���������� � �������
	pNormal->push_back( fnX );
	pNormal->push_back( fnY );
	pNormal->push_back( fnZ );
}

void xmlBranchLoad::DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint 
					, tVecVertex *pTexCoord )
{
	//������� ���������� ����������
	float fS = 0.0f , fT = 0.0f;

	//��������� ���������� ����������
	pPoint->GetAttribute( m_BranchNames.m_sS , &fS );
	pPoint->GetAttribute( m_BranchNames.m_sT , &fT );

	//���������� � �������
	pTexCoord->push_back( fS );
	pTexCoord->push_back( fT );
}

void xmlBranchLoad::DecodeStrips( ticpp::Element* pStrips , int i )
{
	//������� �������
	int iNum = 0;

	//������� ������� �������
	pStrips->GetAttribute( m_BranchNames.m_sNum , &iNum );
	m_pData->m_vBranch[ i ].m_vvIndex.resize( iNum );
	ticpp::Iterator< ticpp::Element > pStrip( m_BranchNames.m_sStrip );

	int iNom = 0;

	//��������� ��� ������� �������������
	for ( pStrip = pStrip.begin( pStrips ); pStrip != pStrip.end(); pStrip++ )
	{
		ticpp::Iterator< ticpp::Element > pInd( m_BranchNames.m_sInd );
		for ( pInd = pInd.begin( &( *pStrip ) ); pInd != pInd.end(); pInd++ )
		{
			int iVal = 0;
			pInd->GetAttribute( m_BranchNames.m_sVal , &iVal );
			m_pData->m_vBranch[ i ].m_vvIndex[ iNom ].push_back( iVal );
		}

		++iNom;
	}
}