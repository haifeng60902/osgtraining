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
	//получить xml тег с сформированными данными

	//получить ссылку на данные ствола
	dataBranch &_data = xmlRoot::Instance().GetDataBranch();

	//формируем корневой узел данных
	TiXmlElement *pBranch = NULL;
	pBranch = new TiXmlElement( m_BranchNames.m_sBranch.c_str() );

	//значение альфа теста
	pBranch->SetAttribute( m_BranchNames.m_sAlfaTest.c_str() , _data.m_fAlphaTestValue );

	//значение альфа теста
	pBranch->SetAttribute( m_BranchNames.m_sTexture.c_str() , _data.m_sTexture.c_str() );

	//заполнить данными о координатах
	FillVertex( _data  ,  pBranch );

	//заполнить индексами
	FillIndexes( _data  ,  pBranch );

	return pBranch;
}

void xmlBranchSave::FillVertex( const dataBranch &_data  , TiXmlElement* root )
{
	//перебрать все шаблоны слоев

	//создать запись для вершин
	TiXmlElement *pVertexs = NULL;
	pVertexs = new TiXmlElement( m_BranchNames.m_sVertexs.c_str() );

	//количество вершин
	pVertexs->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_vCoords.size() / 3 );

	for ( int i = 0; i < _data.m_vCoords.size() / 3; ++i )
	{
		//формирем узел очередной точки
		TiXmlElement *pPoint = new TiXmlElement( m_BranchNames.m_sPoint.c_str() );

		//атрибуты точки
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

void xmlBranchSave::FillIndexes( const dataBranch &_data  , TiXmlElement* root )
{
	//заполнить индексами

	//создать запись для очередного шаблона слоя
	TiXmlElement *pStrips = NULL;
	pStrips = new TiXmlElement( m_BranchNames.m_sStrips.c_str() );

	//количество TRIANGLE_STRIP
	pStrips->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_Strips.size() );

	for ( int i = 0 ; i < _data.m_Strips.size() ; ++i )
	{
		TiXmlElement *pStrip = NULL;
		pStrip = new TiXmlElement( m_BranchNames.m_sStrip.c_str() );

		//количество элементов
		pStrip->SetAttribute( m_BranchNames.m_sNum.c_str() , _data.m_Strips[ i ].size() );

		for ( int j = 0 ; j < _data.m_Strips[ i ].size() ; ++ j )
		{
			TiXmlElement *pInd = NULL;
			pInd = new TiXmlElement( m_BranchNames.m_sInd.c_str() );

			//количество элементов
			pInd->SetAttribute( m_BranchNames.m_sVal.c_str() , _data.m_Strips[ i ][ j ] );

			pStrip->LinkEndChild( pInd );
		}

		pStrips->LinkEndChild( pStrip );
	}

	root->LinkEndChild( pStrips );
}