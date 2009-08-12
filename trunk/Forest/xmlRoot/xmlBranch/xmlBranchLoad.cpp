#include "xmlBranchLoad.h"

#include "xmlBranchNames.h"

xmlBranchLoad::xmlBranchLoad()
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

		//декодировать параметр для альфа теста
		DecodeAttrAlfa( _attr );

		//извлечь данные о вершинах
		DecodeVertexs( pBranch );

		//извлечь данные о индексах
		DecodeStrips( pBranch );
	}
}

void xmlBranchLoad::DecodeAttrAlfa( TiXmlAttribute* _attr )
{
	//декодировать параметр для альфа теста
	while ( _attr )
	{
		//имя атрибута
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//извлекаем значения
		if ( _sAttr == m_BranchNames.m_sAlfaTest )
		{
			double alfa = 0.0;
			_attr->QueryDoubleValue( &alfa );

			m_pDataBranch->m_fAlphaTestValue = alfa;
		}
		else
			if ( _sAttr == m_BranchNames.m_sTexture )
				m_pDataBranch->m_sTexture = _attr->Value();

		//переходим к следующему атрибуту
		_attr = _attr->Next();
	}
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

		//получить указатель на первый атрибут элемента
		TiXmlAttribute* _attr = pElem->FirstAttribute();

		//декодировать параметр точки
		DecodeAttrPoint( _attr );
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

	m_pDataBranch->m_vCoords.push_back( x );
	m_pDataBranch->m_vCoords.push_back( y );
	m_pDataBranch->m_vCoords.push_back( z );

	m_pDataBranch->m_vNormals.push_back( nx );
	m_pDataBranch->m_vNormals.push_back( ny );
	m_pDataBranch->m_vNormals.push_back( nz );

	m_pDataBranch->m_vTexCoords0.push_back( s );
	m_pDataBranch->m_vTexCoords0.push_back( t );
	m_pDataBranch->m_vTexCoords0.push_back( p );
	m_pDataBranch->m_vTexCoords0.push_back( q );
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
			m_pDataBranch->m_Strips.resize( num );
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
			m_pDataBranch->m_Strips[ ind ].push_back( i );
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
