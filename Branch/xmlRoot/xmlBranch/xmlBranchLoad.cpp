#include "xmlBranchLoad.h"

#include "xmlBranchNames.h"

#include "../../ModelScale.h"

xmlBranchLoad::xmlBranchLoad() : m_iLOD( 0 )
{

}

xmlBranchLoad::~xmlBranchLoad()
{

}

void xmlBranchLoad::ParseXml( TiXmlElement* root , dataBranch *_data )
{
	//разбор xml и заполнение бинарных данных
	
	m_pDataBranch = _data;

	//извлечь данные о стволе
	DecodeBranch( root );
}

void xmlBranchLoad::DecodeBranch( TiXmlElement* root )
{
	//извлечь данные о стволе

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sBranch.c_str() );

	if ( node )
	{
		TiXmlElement* pBranch = node->ToElement();

		//извлечь имя элемента
		const char *_name = pBranch->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pBranch->FirstAttribute();

		//декодировать параметр с именем текстуры
		DecodeAttrTexture( _attr );

		//декодировать данные LOD'ов
		DecodeLODs( pBranch );
	}
}

void xmlBranchLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//декодировать параметр с именем текстуры
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sTexture )
			m_pDataBranch->m_sTexture = _attr->Value();

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeLODs( TiXmlElement* root )
{
	//декодировать данные LOD'ов

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sLODs.c_str() );

	if ( node )
	{
		TiXmlElement* pLODs = node->ToElement();

		//извлечь имя элемента
		const char *_name = pLODs->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pLODs->FirstAttribute();

		//узнать количество LOD'ов
		DecodeAttrNumLods( _attr );

		//декодировать данные LOD'а
		DecodeLOD( pLODs );
	}
}

void xmlBranchLoad::DecodeAttrNumLods( TiXmlAttribute* _attr )
{
	//узнать количество LOD'ов
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sNum )
		{
			int iNum = 0;
			_attr->QueryIntValue( &iNum );

			m_pDataBranch->m_vLOD.resize( iNum );
		}

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeLOD( TiXmlElement* root )
{
	//декодировать данные LOD'а

	for ( TiXmlElement *pLOD = root->FirstChildElement() ; pLOD ; pLOD = pLOD->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pLOD->Value();
		std::string _sElem( _name );

		if ( _sElem == m_BranchNames.m_sLOD )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pLOD->FirstAttribute();

			//узнать текущий номер LOD'а
			DecodeAttrLod( _attr );

			//извлечь данные о вершинах
			DecodeVertexs( pLOD );

			//извлечь данные о индексах
			DecodeStrips( pLOD );
		}
	}
}

void xmlBranchLoad::DecodeAttrLod( TiXmlAttribute* _attr )
{
	double alfa = 0.0;

	//узнать текущий номер LOD'а
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sNum )
			_attr->QueryIntValue( &m_iLOD );
		else
			if ( _sAttr == m_BranchNames.m_sAlfaTest )
				_attr->QueryDoubleValue( &alfa );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}

	m_pDataBranch->m_vLOD[ m_iLOD ].m_fAlphaTestValue = alfa;
}

void xmlBranchLoad::DecodeVertexs( TiXmlElement* root )
{
	//извлечь данные о вершинах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sVertexs.c_str() );

	if ( node )
	{
		TiXmlElement* pVertex = node->ToElement();

		//извлечь имя элемента
		const char *_name = pVertex->Value();
		std::string _sElem( _name );

		//извлечь данные о точке
		DecodePoints( pVertex );
	}
	
}

void xmlBranchLoad::DecodePoints( TiXmlElement* root )
{
	//извлечь данные о точке

	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sPoint )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//декодировать параметр точки
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlBranchLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
{
	//декодировать параметр точки
	double x , y , z;
	double nx , ny , nz;
	double s , t , p , q;

	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sX )		
			_attr->QueryDoubleValue( &x );
		else
			if ( _sAttr == m_BranchNames.m_sY )
				_attr->QueryDoubleValue( &y );
			else
				if ( _sAttr == m_BranchNames.m_sZ )
					_attr->QueryDoubleValue( &z );
				else
					if ( _sAttr == m_BranchNames.m_sT )
						_attr->QueryDoubleValue( &t );
					else
						if ( _sAttr == m_BranchNames.m_snX )
							_attr->QueryDoubleValue( &nx );
						else
							if ( _sAttr == m_BranchNames.m_snY )
								_attr->QueryDoubleValue( &ny );
							else
								if ( _sAttr == m_BranchNames.m_snZ )
									_attr->QueryDoubleValue( &nz );
								else
									if ( _sAttr == m_BranchNames.m_sP )
										_attr->QueryDoubleValue( &p );
									else
										if ( _sAttr == m_BranchNames.m_sS )
											_attr->QueryDoubleValue( &s );
										else
											if ( _sAttr == m_BranchNames.m_sQ )
												_attr->QueryDoubleValue( &q );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}

	m_pDataBranch->m_vLOD[ m_iLOD ].m_vCoords.push_back( x * MODEL_KOF_SCALE );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vCoords.push_back( y * MODEL_KOF_SCALE );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vCoords.push_back( z * MODEL_KOF_SCALE );

	m_pDataBranch->m_vLOD[ m_iLOD ].m_vNormals.push_back( nx );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vNormals.push_back( ny );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vNormals.push_back( nz );

	m_pDataBranch->m_vLOD[ m_iLOD ].m_vTexCoords0.push_back( s );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vTexCoords0.push_back( t );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vTexCoords0.push_back( p );
	m_pDataBranch->m_vLOD[ m_iLOD ].m_vTexCoords0.push_back( q );
}

void xmlBranchLoad::DecodeStrips( TiXmlElement* root )
{
	//извлечь данные о индексах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sStrips.c_str() );

	if ( node )
	{
		TiXmlElement* pStrips= node->ToElement();

		//извлечь имя элемента
		const char *_name = pStrips->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pStrips->FirstAttribute();

		//извлечь количество полосок
		DecodeAttrNumStrips( _attr );

		//декодировать полоски
		DecodeStrip( pStrips );
	}
}

void xmlBranchLoad::DecodeAttrNumStrips( TiXmlAttribute* _attr )
{
	//извлечь количество полосок

	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sNum )
		{
			int num;
			_attr->QueryIntValue( &num );
			m_pDataBranch->m_vLOD[ m_iLOD ].m_Strips.resize( num );
		}

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeStrip( TiXmlElement* root )
{
	//декодировать полоски

	int ind = 0;
	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sStrip )
		{
			//декодировать индексы
			DecodeInd( pElem , ind );
			
			++ind;
		}
	}
}

void xmlBranchLoad::DecodeInd( TiXmlElement* root , int ind )
{
//декодировать индексы
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sInd )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//извлечь очередной индекс
			int i = DecodeAttrInd( _attr );
			m_pDataBranch->m_vLOD[ m_iLOD ].m_Strips[ ind ].push_back( i );
		}
	}
}

int xmlBranchLoad::DecodeAttrInd( TiXmlAttribute* _attr )
{
	//извлечь очередной индекс
	int ind = 0;
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sVal )
			_attr->QueryIntValue( &ind );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
	return ind;
}
