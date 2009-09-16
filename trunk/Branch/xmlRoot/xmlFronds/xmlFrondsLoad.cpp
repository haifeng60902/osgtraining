#include "xmlFrondsLoad.h"

#include "xmlFrondsNames.h"

#include "../../ModelScale.h"

xmlFrondsLoad::xmlFrondsLoad() : m_iLOD( 0 )
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

		//������� ������ � ���������
		DecodeTextures( pFronds );

		//������������ ������ LOD'��
		DecodeLODs( pFronds );
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

void xmlFrondsLoad::DecodeLODs( TiXmlElement* root )
{
	//������������ ������ LOD'��
	
	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_FrondsNames.m_sLODs.c_str() );

	if ( node )
	{
		TiXmlElement* pLODs = node->ToElement();

		//������� ��� ��������
		const char *_name = pLODs->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pLODs->FirstAttribute();

		//������ ���������� LOD'��
		DecodeAttrNumLods( _attr );

		//������������ ������ LOD'�
		DecodeLOD( pLODs );
	}
}

void xmlFrondsLoad::DecodeAttrNumLods( TiXmlAttribute* _attr )
{
	//������ ���������� LOD'��
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sNum )
		{
			int iNum = 0;
			_attr->QueryIntValue( &iNum );

			m_pDataFronds->m_vFrLOD.resize( iNum );
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlFrondsLoad::DecodeLOD( TiXmlElement* root )
{
	//������������ ������ LOD'�

	for ( TiXmlElement *pLOD = root->FirstChildElement() ; pLOD ; pLOD = pLOD->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pLOD->Value();
		std::string _sElem( _name );

		if ( _sElem == m_FrondsNames.m_sLOD )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pLOD->FirstAttribute();

			//������ ������� ����� LOD'�
			DecodeAttrLod( _attr );

			//������� ������ � ��������
			DecodeVertexs( pLOD );

			//������� ������ � ��������
			DecodeStrips( pLOD );
		}
	}
}

void xmlFrondsLoad::DecodeAttrLod( TiXmlAttribute* _attr )
{
	double alfa = 0.0;

	//������ ������� ����� LOD'�
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_FrondsNames.m_sNum )
			_attr->QueryIntValue( &m_iLOD );
		else
			if ( _sAttr == m_FrondsNames.m_sAlfaTest )
				_attr->QueryDoubleValue( &alfa );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}

	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_fAlphaTestValue = alfa;
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

	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vCoords.push_back( x * MODEL_KOF_SCALE );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vCoords.push_back( y * MODEL_KOF_SCALE );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vCoords.push_back( z * MODEL_KOF_SCALE );

	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vNormals.push_back( nx );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vNormals.push_back( ny );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vNormals.push_back( nz );

	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vTexCoords0.push_back( s );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vTexCoords0.push_back( t );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vTexCoords0.push_back( p );
	m_pDataFronds->m_vFrLOD[ m_iLOD ].m_vTexCoords0.push_back( q );
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
			m_pDataFronds->m_vFrLOD[ m_iLOD ].m_Strips.resize( num );
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
			m_pDataFronds->m_vFrLOD[ m_iLOD ].m_Strips[ ind ].push_back( i );
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
