#include "xmlLeafLoad.h"

#include "xmlLeafNames.h"

xmlLeafLoad::xmlLeafLoad() : m_pData( NULL )
{

}

xmlLeafLoad::~xmlLeafLoad()
{

}

void xmlLeafLoad::ParseXml( ticpp::Node* pNode , binLeaf *_data )
{
	//разбор xml и заполнение бинарных данных
	m_pData = _data;

	//перейти к узлу fronds
	DecodeSettings( pNode );
}

void xmlLeafLoad::DecodeSettings( ticpp::Node* pNode )
{
	//перейти к узлу branch
	ticpp::Element* pLeaf = pNode->FirstChildElement( m_LeafNames.m_sLeaf ,false );
	if ( pLeaf )
	{

		//извлечь имена текстур
		DecodeTextures( pLeaf->FirstChildElement( m_LeafNames.m_sTextures ,false ) );

		//перейти к узлу с LOD'ами
		ticpp::Element* pLODs = pLeaf->FirstChildElement( m_LeafNames.m_sLODs ,false );
		if ( pLODs )
		{
			//считать количество LOD'ов
			int iSize = 0;
			pLODs->GetAttribute( m_LeafNames.m_sNum , &iSize , false );
			if ( iSize > 0 )
			{
				//выделить память
				m_pData->m_vLeaf.resize( iSize );

				//считать данные LOD'ов
				DecodeLODs( pLODs );
			}
		}
	}
}

void xmlLeafLoad::DecodeTextures( ticpp::Element* pTextures )
{
	//извлечь имена текстур
	if ( pTextures )
	{
		int iSize = 0;
		pTextures->GetAttribute( m_LeafNames.m_sNum , &iSize , false );
		ticpp::Iterator< ticpp::Element > pTexture( m_LeafNames.m_sTexture );
		for ( pTexture = pTexture.begin( pTextures ); pTexture != pTexture.end(); pTexture++ )
		{
			//считать атрибут с именем текстуры
			std::string sTexture;
			pTexture->GetAttribute( m_LeafNames.m_sVal , &sTexture , false );
			m_pData->m_vTextures.push_back( sTexture );
		}
	}
}

void xmlLeafLoad::DecodeLODs( ticpp::Element* pLODs )
{
	//считать данные LOD'ов
	try
	{
		ticpp::Iterator< ticpp::Element > pLOD( m_LeafNames.m_sLOD );
		for ( pLOD = pLOD.begin( pLODs ); pLOD != pLOD.end(); pLOD++ )
		{
			int iNum = -1;
			pLOD->GetAttribute( m_LeafNames.m_sNum , &iNum );
			pLOD->GetAttribute( m_LeafNames.m_sAlfaTest , &m_pData->m_vLeaf[ iNum ].m_fAlfa );

			//считать координаты точки
			DecodePoint( pLOD->FirstChildElement( m_LeafNames.m_sVertexs ) , iNum );
		}

	}
	catch( ticpp::Exception& ex )
	{
		//If any function has an error, execution will enter here.
		//	Report the error
		std::cout << ex.what();
	}
}

void xmlLeafLoad::DecodePoint( ticpp::Element* pVertex , int i )
{
	//считать координаты точки
	int iNum = 0;
	pVertex->GetAttribute( m_LeafNames.m_sNum , &iNum );
	ticpp::Iterator< ticpp::Element > pPoint( m_LeafNames.m_sPoint );
	for ( pPoint = pPoint.begin( pVertex ); pPoint != pPoint.end(); pPoint++ )
	{
		//извлечь координаты вершины
		DecodeVertex( pPoint , &m_pData->m_vLeaf[ i ].m_vVertex );

		//извлечь координаты нормали
		DecodeNormal( pPoint , &m_pData->m_vLeaf[ i ].m_vNormal );

		//извлечь текстурные координаты
		DecodeTexCoord( pPoint , &m_pData->m_vLeaf[ i ].m_vTexCoord , &m_pData->m_vLeaf[ i ].m_vVerOffset );
	}
}

void xmlLeafLoad::DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pVertex )
{
	//извлечь координаты вершины
	float fX = 0.0f , fY = 0.0f , fZ = 0.0f;		//координаты вершины

	//считываем координаты вершины
	pPoint->GetAttribute( m_LeafNames.m_sX , &fX );
	pPoint->GetAttribute( m_LeafNames.m_sY , &fY );
	pPoint->GetAttribute( m_LeafNames.m_sZ , &fZ );

	//запоминаем в векторе
	pVertex->push_back( fX );
	pVertex->push_back( fY );
	pVertex->push_back( fZ );
}

void xmlLeafLoad::DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pNormal )
{
	//извлечь координаты нормали
	float fnX = 0.0f , fnY = 0.0f , fnZ = 0.0f;		//нормаль вершины

	//нормаль
	pPoint->GetAttribute( m_LeafNames.m_snX , &fnX );
	pPoint->GetAttribute( m_LeafNames.m_snY , &fnY );
	pPoint->GetAttribute( m_LeafNames.m_snZ , &fnZ );

	//запоминаем в векторе
	pNormal->push_back( fnX );
	pNormal->push_back( fnY );
	pNormal->push_back( fnZ );
}

void xmlLeafLoad::DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint 
								   , tVecVertex *pTexCoord , tVecVertex *pVerOffset )
{
	//извлечь текстурные координаты
	float fS0 = 0.0f , fT0 = 0.0f;
	float fS1 = 0.0f , fT1 = 0.0f , fP1 = 0.0f;

	//считываем текстурные координаты
	pPoint->GetAttribute( m_LeafNames.m_sS0 , &fS0 );
	pPoint->GetAttribute( m_LeafNames.m_sT0 , &fT0 );

	//
	pPoint->GetAttribute( m_LeafNames.m_sS1 , &fS1 );
	pPoint->GetAttribute( m_LeafNames.m_sT1 , &fT1 );
	pPoint->GetAttribute( m_LeafNames.m_sP1 , &fP1 );

	//запоминаем в векторе
	pTexCoord->push_back( fS0 );
	pTexCoord->push_back( fT0 );
	pVerOffset->push_back( fS1 );
	pVerOffset->push_back( fT1 );
	pVerOffset->push_back( fP1 );
}