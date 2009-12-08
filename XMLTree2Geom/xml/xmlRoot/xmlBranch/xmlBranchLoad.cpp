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
	//разбор xml и заполнение бинарных данных
	m_pData = _data;

	//перейти к узлу branch
	DecodeSettings( pNode );
}

void xmlBranchLoad::DecodeSettings( ticpp::Node* pNode )
{
	//перейти к узлу branch
	ticpp::Element* pBranch = pNode->FirstChildElement( m_BranchNames.m_sBranch ,false );
	if ( pBranch )
	{
		//считать атрибут с именем текстуры
		pBranch->GetAttribute( m_BranchNames.m_sTexture , &m_pData->m_sTexture , false );

		//перейти к узлу с LOD'ами
		ticpp::Element* pLODs = pBranch->FirstChildElement( m_BranchNames.m_sLODs ,false );
		if ( pLODs )
		{
			//считать количество LOD'ов
			int iSize = 0;
			pLODs->GetAttribute( m_BranchNames.m_sNum , &iSize , false );
			if ( iSize > 0 )
			{
				//выделить память
				m_pData->m_vBranch.resize( iSize );

				//считать данные LOD'ов
				DecodeLODs( pLODs );
			}
		}
	}
}

void xmlBranchLoad::DecodeLODs( ticpp::Element* pLODs )
{
	//считать данные LOD'ов
	try
	{
		ticpp::Iterator< ticpp::Element > pLOD( m_BranchNames.m_sLOD );
		for ( pLOD = pLOD.begin( pLODs ); pLOD != pLOD.end(); pLOD++ )
		{
			int iNum = -1;
			pLOD->GetAttribute( m_BranchNames.m_sNum , &iNum );
			pLOD->GetAttribute( m_BranchNames.m_sAlfaTest , &m_pData->m_vBranch[ iNum ].m_fAlfa );

			//считать координаты точки
			DecodePoint( pLOD->FirstChildElement( m_BranchNames.m_sVertexs ) , iNum );

			//считать индексы
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
	//считать координаты точки
	int iNum = 0;
	pVertex->GetAttribute( m_BranchNames.m_sNum , &iNum );
	ticpp::Iterator< ticpp::Element > pPoint( m_BranchNames.m_sPoint );
	for ( pPoint = pPoint.begin( pVertex ); pPoint != pPoint.end(); pPoint++ )
	{
		//извлечь координаты вершины
		DecodeVertex( pPoint , &m_pData->m_vBranch[ i ].m_vVertex );

		//извлечь координаты нормали
		DecodeNormal( pPoint , &m_pData->m_vBranch[ i ].m_vNormal );

		//извлечь текстурные координаты
		DecodeTexCoord( pPoint , &m_pData->m_vBranch[ i ].m_vTexCoord );
	}
}

void xmlBranchLoad::DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pVertex )
{
	//извлечь координаты вершины
	float fX = 0.0f , fY = 0.0f , fZ = 0.0f;		//координаты вершины

	//считываем координаты вершины
	pPoint->GetAttribute( m_BranchNames.m_sX , &fX );
	pPoint->GetAttribute( m_BranchNames.m_sY , &fY );
	pPoint->GetAttribute( m_BranchNames.m_sZ , &fZ );

	//запоминаем в векторе
	pVertex->push_back( fX );
	pVertex->push_back( fY );
	pVertex->push_back( fZ );
}

void xmlBranchLoad::DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint 
								 , tVecVertex *pNormal )
{
	//извлечь координаты нормали
	float fnX = 0.0f , fnY = 0.0f , fnZ = 0.0f;		//нормаль вершины

	//нормаль
	pPoint->GetAttribute( m_BranchNames.m_snX , &fnX );
	pPoint->GetAttribute( m_BranchNames.m_snY , &fnY );
	pPoint->GetAttribute( m_BranchNames.m_snZ , &fnZ );

	//запоминаем в векторе
	pNormal->push_back( fnX );
	pNormal->push_back( fnY );
	pNormal->push_back( fnZ );
}

void xmlBranchLoad::DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint 
					, tVecVertex *pTexCoord )
{
	//извлечь текстурные координаты
	float fS = 0.0f , fT = 0.0f;

	//считываем текстурные координаты
	pPoint->GetAttribute( m_BranchNames.m_sS , &fS );
	pPoint->GetAttribute( m_BranchNames.m_sT , &fT );

	//запоминаем в векторе
	pTexCoord->push_back( fS );
	pTexCoord->push_back( fT );
}

void xmlBranchLoad::DecodeStrips( ticpp::Element* pStrips , int i )
{
	//считать индексы
	int iNum = 0;

	//считать сколько полосок
	pStrips->GetAttribute( m_BranchNames.m_sNum , &iNum );
	m_pData->m_vBranch[ i ].m_vvIndex.resize( iNum );
	ticpp::Iterator< ticpp::Element > pStrip( m_BranchNames.m_sStrip );

	int iNom = 0;

	//перебрать все полоски треугольников
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