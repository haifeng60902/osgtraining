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
	//������ xml � ���������� �������� ������

	m_pDataFronds = _data;

	//������� ������ � ������
	DecodeFronds( root );
}

void xmlFrondsLoad::DecodeFronds( TiXmlElement* root )
{
	//������� ������ � ������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sFronds.c_str() );

	if ( node )
	{
		TiXmlElement* pFronds = node->ToElement();

		//������� ��� ��������
		const char *_name = pFronds->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pFronds->FirstAttribute();

		//������������ �������� ��� ����� �����
		DecodeAttrAlfa( _attr );

		//������� ������ � ���������
		DecodeTextures( pFronds );

		//������� ������ � ��������
		DecodeVertexs( pFronds );

		//������� ������ � ��������
		DecodeStrips( pFronds );
	}
}

void xmlFrondsLoad::DecodeAttrAlfa( TiXmlAttribute* _attr )
{
	//������������ �������� ��� ����� �����
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sAlfaTest )
		{
			double alfa = 0.0;
			_attr->QueryDoubleValue( &alfa );

			m_pDataFronds->m_fAlphaTestValue = alfa;
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeTextures( TiXmlElement* root )
{
	//������� ������ � ���������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sTextures.c_str() );

	if ( node )
	{
		TiXmlElement* pTextures = node->ToElement();

		//������� ��� ��������
		const char *_name = pTextures->Value();
		std::string _sElem( _name );

		//������� ������ � ��������
		DecodeTexture( pTextures );
	}

}

void xmlFrondsLoad::DecodeTexture( TiXmlElement* root )
{
	//������� ������ � ��������
	
	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sTexture )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������������ ������� ��� ��������
			DecodeAttrTexture( _attr );
		}
	}
}

void xmlFrondsLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//������������ ������� ��� ��������
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sVal )
			m_pDataFronds->m_vTextures.push_back( _attr->Value() );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeVertexs( TiXmlElement* root )
{
	//������� ������ � ��������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sVertexs.c_str() );

	if ( node )
	{
		TiXmlElement* pVertex = node->ToElement();

		//������� ��� ��������
		const char *_name = pVertex->Value();
		std::string _sElem( _name );

		//������� ������ � �����
		DecodePoints( pVertex );
	}
}

void xmlFrondsLoad::DecodePoints( TiXmlElement* root )
{
	//������� ������ � �����

	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sPoint )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������������ �������� �����
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlFrondsLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
{
	//������������ �������� �����
	double x , y , z;
	double nx , ny , nz;
	double s , t , p , q;

	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
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

		//��������� � ���������� ��������
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
	//������� ������ � ��������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sStrips.c_str() );

	if ( node )
	{
		TiXmlElement* pStrips= node->ToElement();

		//������� ��� ��������
		const char *_name = pStrips->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pStrips->FirstAttribute();

		//������� ���������� �������
		DecodeAttrNumStrips( _attr );

		//������������ �������
		DecodeStrip( pStrips );
	}
}

void xmlFrondsLoad::DecodeAttrNumStrips( TiXmlAttribute* _attr )
{
	//������� ���������� �������

	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sNum )
		{
			int num;
			_attr->QueryIntValue( &num );
			m_pDataFronds->m_Strips.resize( num );
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeStrip( TiXmlElement* root )
{
	//������������ �������

	int ind = 0;
	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sStrip )
		{
			//������������ �������
			DecodeInd( pElem , ind );

			++ind;
		}
	}
}

void xmlFrondsLoad::DecodeInd( TiXmlElement* root , int ind )
{
	//������������ �������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_FrondsNames.m_sInd )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������� ��������� ������
			int i = DecodeAttrInd( _attr );
			m_pDataFronds->m_Strips[ ind ].push_back( i );
		}
	}
}

int xmlFrondsLoad::DecodeAttrInd( TiXmlAttribute* _attr )
{
	//������� ��������� ������
	int ind = 0;
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sVal )
			_attr->QueryIntValue( &ind );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
	return ind;
}
