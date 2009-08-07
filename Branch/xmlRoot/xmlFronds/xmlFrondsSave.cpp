#include "xmlFrondsSave.h"

#include "../xmlRoot.h"
#include "xmlFrondsNames.h"

xmlFrondsSave::xmlFrondsSave()
{

}

xmlFrondsSave::~xmlFrondsSave()
{

}

TiXmlElement* xmlFrondsSave::GetXmlData()
{
	//получить xml тег с сформированными данными

	//получить ссылку на данные веток
	dataFronds &_data = xmlRoot::Instance().GetDataFronds();

	//формируем корневой узел данных
	TiXmlElement *pFronds = NULL;
	pFronds = new TiXmlElement( m_FrondsNames.m_sFronds.c_str() );

	//значение альфа теста
	pFronds->SetDoubleAttribute( m_FrondsNames.m_sAlfaTest.c_str() , _data.m_fAlphaTestValue );

	//заполнить данными о текстурах
	FillTextures( _data  , pFronds );

	//заполнить данными о координатах
	FillVertex( _data  ,  pFronds );

	//заполнить индексами
	FillIndexes( _data  ,  pFronds );

	return pFronds;
}

void xmlFrondsSave::FillTextures( const dataFronds &_data  , TiXmlElement* root )
{
	//заполнить данными о текстурах

	//создать запись для текстур
	TiXmlElement *pTextures = NULL;
	pTextures = new TiXmlElement( m_FrondsNames.m_sTextures.c_str() );

	//количество текстур
	pTextures->SetAttribute( m_FrondsNames.m_sNum.c_str() , _data.m_vTextures.size() );

	for ( int i = 0 ; i < _data.m_vTextures.size() ; ++i )
	{
		TiXmlElement *pTexture = NULL;
		pTexture = new TiXmlElement( m_FrondsNames.m_sTexture.c_str() );

		//количество текстур
		pTexture->SetAttribute( m_FrondsNames.m_sVal.c_str() , _data.m_vTextures[ i ].c_str() );

		pTextures->LinkEndChild( pTexture );
	}

	root->LinkEndChild( pTextures );
}

void xmlFrondsSave::FillVertex( const dataFronds &_data  , TiXmlElement* root )
{
	//создать запись для вершин
	TiXmlElement *pVertexs = NULL;
	pVertexs = new TiXmlElement( m_FrondsNames.m_sVertexs.c_str() );

	//количество вершин
	pVertexs->SetAttribute( m_FrondsNames.m_sNum.c_str() , _data.m_vCoords.size() / 3 );

	for ( int i = 0; i < _data.m_vCoords.size() / 3; ++i )
	{
		//формирем узел очередной точки
		TiXmlElement *pPoint = new TiXmlElement( m_FrondsNames.m_sPoint.c_str() );

		//атрибуты точки
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sX.c_str() , _data.m_vCoords[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sY.c_str() , _data.m_vCoords[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sZ.c_str() , _data.m_vCoords[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_FrondsNames.m_snX.c_str() , _data.m_vNormals[ i * 3 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_snY.c_str() , _data.m_vNormals[ i * 3 + 1 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_snZ.c_str() , _data.m_vNormals[ i * 3 + 2 ] );

		pPoint->SetDoubleAttribute( m_FrondsNames.m_sS.c_str() , _data.m_vTexCoords0[ i * 4 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sT.c_str() , _data.m_vTexCoords0[ i * 4 + 1 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sP.c_str() , _data.m_vTexCoords0[ i * 4 + 2 ] );
		pPoint->SetDoubleAttribute( m_FrondsNames.m_sQ.c_str() , _data.m_vTexCoords0[ i * 4 + 3 ] );

		pVertexs->LinkEndChild( pPoint );
	}

	root->LinkEndChild( pVertexs );
}

void xmlFrondsSave::FillIndexes( const dataFronds &_data  , TiXmlElement* root )
{
	//заполнить индексами

	TiXmlElement *pStrips = NULL;
	pStrips = new TiXmlElement( m_FrondsNames.m_sStrips.c_str() );

	//количество TRIANGLE_STRIP
	pStrips->SetAttribute( m_FrondsNames.m_sNum.c_str() , _data.m_Strips.size() );

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		TiXmlElement *pStrip = NULL;
		pStrip = new TiXmlElement( m_FrondsNames.m_sStrip.c_str() );

		//количество элементов
		pStrip->SetAttribute( m_FrondsNames.m_sNum.c_str() , _data.m_Strips[ i ].size() );

		for ( int j = 0 ; j < _data.m_Strips[ i ].size() ; ++ j )
		{
			TiXmlElement *pInd = NULL;
			pInd = new TiXmlElement( m_FrondsNames.m_sInd.c_str() );

			//количество элементов
			pInd->SetAttribute( m_FrondsNames.m_sVal.c_str() , _data.m_Strips[ i ][ j ] );

			pStrip->LinkEndChild( pInd );
		}

		pStrips->LinkEndChild( pStrip );
	}

	root->LinkEndChild( pStrips );
}
