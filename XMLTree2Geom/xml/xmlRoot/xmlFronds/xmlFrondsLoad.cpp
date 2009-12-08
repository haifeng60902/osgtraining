#include "xmlFrondsLoad.h"

#include "xmlFrondsNames.h"

xmlFrondsLoad::xmlFrondsLoad() : m_pData( NULL )
{

}

xmlFrondsLoad::~xmlFrondsLoad()
{

}

void xmlFrondsLoad::ParseXml( ticpp::Node* pNode , binFronds *_data )
{
	//разбор xml и заполнение бинарных данных
	m_pData = _data;

	//перейти к узлу fronds
	DecodeSettings( pNode );
}

void xmlFrondsLoad::DecodeSettings( ticpp::Node* pNode )
{
	//перейти к узлу branch
	ticpp::Element* pFronds = pNode->FirstChildElement( m_FrondsNames.m_sFronds ,false );
	if ( pFronds )
	{
		
		//извлечь имена текстур
		DecodeTextures( pFronds->FirstChildElement( m_FrondsNames.m_sTextures ,false ) );

		//перейти к узлу с LOD'ами
		ticpp::Element* pLODs = pFronds->FirstChildElement( m_FrondsNames.m_sLODs ,false );
		if ( pLODs )
		{
			//считать количество LOD'ов
			int iSize = 0;
			pLODs->GetAttribute( m_FrondsNames.m_sNum , &iSize , false );
			if ( iSize > 0 )
			{
				//выделить память
				m_pData->m_vFronds.resize( iSize );

				//считать данные LOD'ов
				DecodeLODs( pLODs );
			}
		}
	}
}

void xmlFrondsLoad::DecodeTextures( ticpp::Element* pTextures )
{
	//извлечь имена текстур
	if ( pTextures )
	{
		int iSize = 0;
		pTextures->GetAttribute( m_FrondsNames.m_sNum , &iSize , false );
		ticpp::Iterator< ticpp::Element > pTexture( m_FrondsNames.m_sTexture );
		for ( pTexture = pTexture.begin( pTextures ); pTexture != pTexture.end(); pTexture++ )
		{
			//считать атрибут с именем текстуры
			pTexture->GetAttribute( m_FrondsNames.m_sVal , &m_pData->m_sTexture , false );
		}
	}
}

void xmlFrondsLoad::DecodeLODs( ticpp::Element* pLODs )
{
	//считать данные LOD'ов
	try
	{
		ticpp::Iterator< ticpp::Element > pLOD( m_FrondsNames.m_sLOD );
		for ( pLOD = pLOD.begin( pLODs ); pLOD != pLOD.end(); pLOD++ )
		{
			int iNum = -1;
			pLOD->GetAttribute( m_FrondsNames.m_sNum , &iNum );
			pLOD->GetAttribute( m_FrondsNames.m_sAlfaTest , &m_pData->m_vFronds[ iNum ].m_fAlfa );

			//считать координаты точки
			DecodePoint( pLOD->FirstChildElement( m_FrondsNames.m_sVertexs ) , iNum );

			//считать индексы
			DecodeStrips( pLOD->FirstChildElement( m_FrondsNames.m_sStrips ) , iNum );
		}

	}
	catch( ticpp::Exception& ex )
	{
		//If any function has an error, execution will enter here.
		//	Report the error
		std::cout << ex.what();
	}
}

void xmlFrondsLoad::DecodePoint( ticpp::Element* pVertex , int i )
{
	//считать координаты точки
	int iNum = 0;
	pVertex->GetAttribute( m_FrondsNames.m_sNum , &iNum );
	ticpp::Iterator< ticpp::Element > pPoint( m_FrondsNames.m_sPoint );
	for ( pPoint = pPoint.begin( pVertex ); pPoint != pPoint.end(); pPoint++ )
	{
		//извлечь координаты вершины
		DecodeVertex( pPoint , &m_pData->m_vFronds[ i ].m_vVertex );

		//извлечь координаты нормали
		DecodeNormal( pPoint , &m_pData->m_vFronds[ i ].m_vNormal );

		//извлечь текстурные координаты
		DecodeTexCoord( pPoint , &m_pData->m_vFronds[ i ].m_vTexCoord );
	}
}

void xmlFrondsLoad::DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pVertex )
{
	//извлечь координаты вершины
	float fX = 0.0f , fY = 0.0f , fZ = 0.0f;		//координаты вершины

	//считываем координаты вершины
	pPoint->GetAttribute( m_FrondsNames.m_sX , &fX );
	pPoint->GetAttribute( m_FrondsNames.m_sY , &fY );
	pPoint->GetAttribute( m_FrondsNames.m_sZ , &fZ );

	//запоминаем в векторе
	pVertex->push_back( fX );
	pVertex->push_back( fY );
	pVertex->push_back( fZ );
}

void xmlFrondsLoad::DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pNormal )
{
	//извлечь координаты нормали
	float fnX = 0.0f , fnY = 0.0f , fnZ = 0.0f;		//нормаль вершины

	//нормаль
	pPoint->GetAttribute( m_FrondsNames.m_snX , &fnX );
	pPoint->GetAttribute( m_FrondsNames.m_snY , &fnY );
	pPoint->GetAttribute( m_FrondsNames.m_snZ , &fnZ );

	//запоминаем в векторе
	pNormal->push_back( fnX );
	pNormal->push_back( fnY );
	pNormal->push_back( fnZ );
}

void xmlFrondsLoad::DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint 
								   , tVecVertex *pTexCoord )
{
	//извлечь текстурные координаты
	float fS = 0.0f , fT = 0.0f;

	//считываем текстурные координаты
	pPoint->GetAttribute( m_FrondsNames.m_sS , &fS );
	pPoint->GetAttribute( m_FrondsNames.m_sT , &fT );

	//запоминаем в векторе
	pTexCoord->push_back( fS );
	pTexCoord->push_back( fT );
}

void xmlFrondsLoad::DecodeStrips( ticpp::Element* pStrips , int i )
{
	//считать индексы
	int iNum = 0;

	//считать сколько полосок
	pStrips->GetAttribute( m_FrondsNames.m_sNum , &iNum );
	m_pData->m_vFronds[ i ].m_vvIndex.resize( iNum );
	ticpp::Iterator< ticpp::Element > pStrip( m_FrondsNames.m_sStrip );

	int iNom = 0;

	//перебрать все полоски треугольников
	for ( pStrip = pStrip.begin( pStrips ); pStrip != pStrip.end(); pStrip++ )
	{
		ticpp::Iterator< ticpp::Element > pInd( m_FrondsNames.m_sInd );
		for ( pInd = pInd.begin( &( *pStrip ) ); pInd != pInd.end(); pInd++ )
		{
			int iVal = 0;
			pInd->GetAttribute( m_FrondsNames.m_sVal , &iVal );
			m_pData->m_vFronds[ i ].m_vvIndex[ iNom ].push_back( iVal );
		}

		++iNom;
	}
}