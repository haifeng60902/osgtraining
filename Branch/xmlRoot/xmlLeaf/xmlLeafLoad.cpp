#include "xmlLeafLoad.h"

#include "xmlLeafNames.h"

xmlLeafLoad::xmlLeafLoad()
{

}

xmlLeafLoad::~xmlLeafLoad()
{

}

void xmlLeafLoad::ParseXml( TiXmlElement* root , dataLeaf *_data )
{
	//разбор xml и заполнение бинарных данных

	m_pDataLeaf = _data;

	//извлечь данные о листве
	DecodeLeaf( root );
}

void xmlLeafLoad::DecodeLeaf( TiXmlElement* root )
{
	//извлечь данные о листве

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sLeaf.c_str() );

	if ( node )
	{
		TiXmlElement* pLeaf = node->ToElement();

		//извлечь имя элемента
		const char *_name = pLeaf->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pLeaf->FirstAttribute();

		//декодировать параметр для альфа теста
		DecodeAttrAlfa( _attr );

		//извлечь данные о текстурах
		DecodeTextures( pLeaf );

		//извлечь данные о вершинах
		DecodeVertexs( pLeaf );

		//извлечь данные о влиянии ветра
		DecodeWind( pLeaf );
	}
}

void xmlLeafLoad::DecodeAttrAlfa( TiXmlAttribute* _attr )
{
	//декодировать параметр для альфа теста
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_LeafNames.m_sAlfaTest )
		{
			double alfa = 0.0;
			_attr->QueryDoubleValue( &alfa );

			m_pDataLeaf->m_fAlphaTestValue = alfa;
		}

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlLeafLoad::DecodeTextures( TiXmlElement* root )
{
	//извлечь данные о текстурах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sTextures.c_str() );

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

void xmlLeafLoad::DecodeTexture( TiXmlElement* root )
{
	//извлечь данные о текстуре

	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_LeafNames.m_sTexture )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//декодировать атрибут имя текстуры
			DecodeAttrTexture( _attr );
		}
	}
}

void xmlLeafLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//декодировать атрибут имя текстуры
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_LeafNames.m_sVal )
			m_pDataLeaf->m_vTextures.push_back( _attr->Value() );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}

void xmlLeafLoad::DecodeVertexs( TiXmlElement* root )
{
	//извлечь данные о вершинах

	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sVertexs.c_str() );

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

void xmlLeafLoad::DecodePoints( TiXmlElement* root )
{
	//извлечь данные о точке

	//перебор всех категорий
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//извлечь имя элемента
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_LeafNames.m_sPoint )
		{
			//получить указатель на первый атрибут элемента
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//декодировать параметр точки
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlLeafLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
{
	//декодировать параметр точки
	double x , y , z;
	double nx , ny , nz;
	double s0 , t0 , p0 , q0;
	double s1 , t1 , p1;

	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_LeafNames.m_sX )		
			_attr->QueryDoubleValue( &x );
		else
			if ( _sAttr == m_LeafNames.m_sY )
				_attr->QueryDoubleValue( &y );
			else
				if ( _sAttr == m_LeafNames.m_sZ )
					_attr->QueryDoubleValue( &z );
				else
					if ( _sAttr == m_LeafNames.m_sT0 )
						_attr->QueryDoubleValue( &t0 );
					else
						if ( _sAttr == m_LeafNames.m_snX )
							_attr->QueryDoubleValue( &nx );
						else
							if ( _sAttr == m_LeafNames.m_snY )
								_attr->QueryDoubleValue( &ny );
							else
								if ( _sAttr == m_LeafNames.m_snZ )
									_attr->QueryDoubleValue( &nz );
								else
									if ( _sAttr == m_LeafNames.m_sP0 )
										_attr->QueryDoubleValue( &p0 );
									else
										if ( _sAttr == m_LeafNames.m_sS0 )
											_attr->QueryDoubleValue( &s0 );
										else
											if ( _sAttr == m_LeafNames.m_sQ0 )
												_attr->QueryDoubleValue( &q0 );
											else
												if ( _sAttr == m_LeafNames.m_sS1 )
													_attr->QueryDoubleValue( &s1 );
												else
													if ( _sAttr == m_LeafNames.m_sT1 )
														_attr->QueryDoubleValue( &t1 );
													else
														if ( _sAttr == m_LeafNames.m_sP1 )
															_attr->QueryDoubleValue( &p1 );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}

	m_pDataLeaf->m_vCoords.push_back( x );
	m_pDataLeaf->m_vCoords.push_back( y );
	m_pDataLeaf->m_vCoords.push_back( z );

	m_pDataLeaf->m_vNormals.push_back( nx );
	m_pDataLeaf->m_vNormals.push_back( ny );
	m_pDataLeaf->m_vNormals.push_back( nz );

	m_pDataLeaf->m_vTexCoords0.push_back( s0 );
	m_pDataLeaf->m_vTexCoords0.push_back( t0 );
	m_pDataLeaf->m_vTexCoords0.push_back( p0 );
	m_pDataLeaf->m_vTexCoords0.push_back( q0 );

	m_pDataLeaf->m_vTexCoords1.push_back( s1 );
	m_pDataLeaf->m_vTexCoords1.push_back( t1 );
	m_pDataLeaf->m_vTexCoords1.push_back( p1 );
}

void xmlLeafLoad::DecodeWind( TiXmlElement* root )
{
	//извлечь данные о влиянии ветра
	//извлечение информации из узла XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sWind.c_str() );

	if ( node )
	{
		TiXmlElement* pWind = node->ToElement();

		//извлечь имя элемента
		const char *_name = pWind->Value();
		std::string _sElem( _name );

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pWind->FirstAttribute();

		//извлечь атрибуты ветра
		DecodeAttrWind( _attr );
	}
}

void xmlLeafLoad::DecodeAttrWind( TiXmlAttribute* _attr )
{
	double dFrY = 0;
	double dFrZ = 0;
	//извлечь атрибуты ветра
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		//if ( _sAttr == m_LeafNames.m_sFreqY )

		//	_attr->QueryDoubleValue( &m_pDataLeaf->m_fFreqY );

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
}