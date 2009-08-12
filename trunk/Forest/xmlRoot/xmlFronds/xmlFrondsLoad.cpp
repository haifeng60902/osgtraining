#include "xmlFrondsLoad.h"

#include "xmlFrondsNames.h"

xmlFrondsLoad::xmlFrondsLoad()
{

}

xmlFrondsLoad::~xmlFrondsLoad()
{

}

void xmlFrondsLoad::ParseXml( TiXmlElement* root , dataFronds *_data )
{
	//разбор xml и заполнение бинарных данных

	m_pDataFronds = _data;

	//извлечь данные о ветках
	DecodeFronds( root );
}

void xmlFrondsLoad::DecodeFronds( TiXmlElement* root )
{
	//извлечь данные о ветках

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sFronds.c_str() );

	if ( node )
	{
		TiXmlElement* pFronds = node->ToElement();

		//извлечь имя элемента
		const char *_name = pFronds->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pFronds->FirstAttribute();

		//декодировать параметр для альфа теста
		DecodeAttrAlfa( _attr );

		//извлечь данные о текстурах
		DecodeTextures( pFronds );

		//извлечь данные о вершинах
		DecodeVertexs( pFronds );

		//извлечь данные о индексах
		DecodeStrips( pFronds );
	}
}

void xmlFrondsLoad::DecodeAttrAlfa( TiXmlAttribute* _attr )
{
	//декодировать параметр для альфа теста
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_FrondsNames.m_sAlfaTest )
		{
			double alfa = 0.0;
			_attr->QueryDoubleValue( &alfa );

			m_pDataFronds->m_fAlphaTestValue = alfa;
		}

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeTextures( TiXmlElement* root )
{
	//извлечь данные о текстурах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sTextures.c_str() );

	if ( node )
	{
		TiXmlElement* pTextures = node->ToElement();

		//извлечь имя элемента
		const char *_name = pTextures->Value();
		std::string _sElem( _name );

		//извлечь данные о текстуре
		DecodeTexture( pTextures );
	}

}

void xmlFrondsLoad::DecodeTexture( TiXmlElement* root )
{
	//извлечь данные о текстуре
	
	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sTexture )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//декодировать атрибут имя текстуры
			DecodeAttrTexture( _attr );
		}
	}
}

void xmlFrondsLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//декодировать атрибут имя текстуры
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_FrondsNames.m_sVal )
			m_pDataFronds->m_vTextures.push_back( _attr->Value() );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeVertexs( TiXmlElement* root )
{
	//извлечь данные о вершинах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sVertexs.c_str() );

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

void xmlFrondsLoad::DecodePoints( TiXmlElement* root )
{
	//извлечь данные о точке

	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sPoint )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//декодировать параметр точки
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlFrondsLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
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
		if ( _sAttr == m_FrondsNames.m_sX )		
			_attr->QueryDoubleValue( &x );
		else
			if ( _sAttr == m_FrondsNames.m_sY )
				_attr->QueryDoubleValue( &y );
			else
				if ( _sAttr == m_FrondsNames.m_sZ )
					_attr->QueryDoubleValue( &z );
				else
					if ( _sAttr == m_FrondsNames.m_sT )
						_attr->QueryDoubleValue( &t );
					else
						if ( _sAttr == m_FrondsNames.m_snX )
							_attr->QueryDoubleValue( &nx );
						else
							if ( _sAttr == m_FrondsNames.m_snY )
								_attr->QueryDoubleValue( &ny );
							else
								if ( _sAttr == m_FrondsNames.m_snZ )
									_attr->QueryDoubleValue( &nz );
								else
									if ( _sAttr == m_FrondsNames.m_sP )
										_attr->QueryDoubleValue( &p );
									else
										if ( _sAttr == m_FrondsNames.m_sS )
											_attr->QueryDoubleValue( &s );
										else
											if ( _sAttr == m_FrondsNames.m_sQ )
												_attr->QueryDoubleValue( &q );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}

	m_pDataFronds->m_vCoords.push_back( x );
	m_pDataFronds->m_vCoords.push_back( y );
	m_pDataFronds->m_vCoords.push_back( z );

	m_pDataFronds->m_vNormals.push_back( nx );
	m_pDataFronds->m_vNormals.push_back( ny );
	m_pDataFronds->m_vNormals.push_back( nz );

	m_pDataFronds->m_vTexCoords0.push_back( s );
	m_pDataFronds->m_vTexCoords0.push_back( t );
	m_pDataFronds->m_vTexCoords0.push_back( p );
	m_pDataFronds->m_vTexCoords0.push_back( q );
}

void xmlFrondsLoad::DecodeStrips( TiXmlElement* root )
{
	//извлечь данные о индексах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sStrips.c_str() );

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

void xmlFrondsLoad::DecodeAttrNumStrips( TiXmlAttribute* _attr )
{
	//извлечь количество полосок

	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_FrondsNames.m_sNum )
		{
			int num;
			_attr->QueryIntValue( &num );
			m_pDataFronds->m_Strips.resize( num );
		}

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeStrip( TiXmlElement* root )
{
	//декодировать полоски

	int ind = 0;
	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sStrip )
		{
			//декодировать индексы
			DecodeInd( pElem , ind );

			++ind;
		}
	}
}

void xmlFrondsLoad::DecodeInd( TiXmlElement* root , int ind )
{
	//декодировать индексы
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sInd )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//извлечь очередной индекс
			int i = DecodeAttrInd( _attr );
			m_pDataFronds->m_Strips[ ind ].push_back( i );
		}
	}
}

int xmlFrondsLoad::DecodeAttrInd( TiXmlAttribute* _attr )
{
	//извлечь очередной индекс
	int ind = 0;
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_FrondsNames.m_sVal )
			_attr->QueryIntValue( &ind );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
	return ind;
}
