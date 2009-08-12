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
	//получить xml тег с сформированными данными

	//получить ссылку на данные веток
	dataLeaf &_data = xmlRoot::Instance().GetDataLeaf();

	//формируем корневой узел данных
	TiXmlElement *pLeaf = NULL;
	pLeaf = new TiXmlElement( m_LeafNames.m_sLeaf.c_str() );

	//значение альфа теста
	pLeaf->SetDoubleAttribute( m_LeafNames.m_sAlfaTest.c_str() , _data.m_fAlphaTestValue );

	//заполнить данными о текстурах
	FillTextures( _data  , pLeaf );

	//заполнить данными о координатах
	FillVertex( _data  ,  pLeaf );

	//заполнить данными о ветре
	FillWind( pLeaf );

	return pLeaf;
}

void xmlLeafSave::FillTextures( const dataLeaf &_data  , TiXmlElement* root )
{
	//заполнить данными о текстурах

	//создать запись для текстур
	TiXmlElement *pTextures = NULL;
	pTextures = new TiXmlElement( m_LeafNames.m_sTextures.c_str() );

	//количество текстур
	pTextures->SetAttribute( m_LeafNames.m_sNum.c_str() , _data.m_vTextures.size() );

	for ( int i = 0 ; i < _data.m_vTextures.size() ; ++i )
	{
		TiXmlElement *pTexture = NULL;
		pTexture = new TiXmlElement( m_LeafNames.m_sTexture.c_str() );

		//количество текстур
		pTexture->SetAttribute( m_LeafNames.m_sVal.c_str() , _data.m_vTextures[ i ].c_str() );

		pTextures->LinkEndChild( pTexture );
	}

	root->LinkEndChild( pTextures );
}

void xmlLeafSave::FillVertex( const dataLeaf &_data  , TiXmlElement* root )
{
	//создать запись для вершин
	TiXmlElement *pVertexs = NULL;
	pVertexs = new TiXmlElement( m_LeafNames.m_sVertexs.c_str() );

	//количество вершин
	pVertexs->SetAttribute( m_LeafNames.m_sNum.c_str() , _data.m_vCoords.size() / 3 );

	for ( int i = 0; i < _data.m_vCoords.size() / 3; ++i )
	{
		//формирем узел очередной точки
		TiXmlElement *pPoint = new TiXmlElement( m_LeafNames.m_sPoint.c_str() );

		//атрибуты точки
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
	//заполнить данными о ветре

	//создать запись для ветра
	TiXmlElement *pWind = NULL;
	pWind = new TiXmlElement( m_LeafNames.m_sWind.c_str() );

	//частота вращения вокруг оси Y
	pWind->SetAttribute( m_LeafNames.m_sFreqY.c_str() , 0 );

	//амплитуда вращения вокруг оси Y
	pWind->SetAttribute( m_LeafNames.m_sAmplY.c_str() , 0 );

	//частота вращения вокруг оси Z
	pWind->SetAttribute( m_LeafNames.m_sFreqZ.c_str() , 0 );

	//амплитуда вращения вокруг оси Z
	pWind->SetAttribute( m_LeafNames.m_sAmplZ.c_str() , 0 );

	root->LinkEndChild( pWind );
}