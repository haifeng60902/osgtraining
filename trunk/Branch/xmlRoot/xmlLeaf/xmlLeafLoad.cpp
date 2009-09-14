#include "xmlLeafLoad.h"

#include "xmlLeafNames.h"

xmlLeafLoad::xmlLeafLoad() : m_iLOD( 0 )
{

}

xmlLeafLoad::~xmlLeafLoad()
{

}

void xmlLeafLoad::ParseXml( TiXmlElement* root , dataLeaf *_data )
{
	//������ xml � ���������� �������� ������

	m_pDataLeaf = _data;

	//������� ������ � ������
	DecodeLeaf( root );
}

void xmlLeafLoad::DecodeLeaf( TiXmlElement* root )
{
	//������� ������ � ������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sLeaf.c_str() );

	if ( node )
	{
		TiXmlElement* pLeaf = node->ToElement();

		//������� ��� ��������
		const char *_name = pLeaf->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pLeaf->FirstAttribute();

		//������� ������ � ���������
		DecodeTextures( pLeaf );

		//������� ������ � ������� �����
		DecodeWind( pLeaf );

		//������������ ������ LOD'��
		DecodeLODs( pLeaf );
	}
}

void xmlLeafLoad::DecodeTextures( TiXmlElement* root )
{
	//������� ������ � ���������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sTextures.c_str() );

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

void xmlLeafLoad::DecodeTexture( TiXmlElement* root )
{
	//������� ������ � ��������

	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_LeafNames.m_sTexture )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������������ ������� ��� ��������
			DecodeAttrTexture( _attr );
		}
	}
}

void xmlLeafLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//������������ ������� ��� ��������
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_LeafNames.m_sVal )
			m_pDataLeaf->m_vTextures.push_back( _attr->Value() );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlLeafLoad::DecodeLODs( TiXmlElement* root )
{
	//������������ ������ LOD'��

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sLODs.c_str() );

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

void xmlLeafLoad::DecodeAttrNumLods( TiXmlAttribute* _attr )
{
	//������ ���������� LOD'��
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_LeafNames.m_sNum )
		{
			int iNum = 0;
			_attr->QueryIntValue( &iNum );

			m_pDataLeaf->m_vLfLOD.resize( iNum );
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlLeafLoad::DecodeLOD( TiXmlElement* root )
{
	//������������ ������ LOD'�

	for ( TiXmlElement *pLOD = root->FirstChildElement() ; pLOD ; pLOD = pLOD->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pLOD->Value();
		std::string _sElem( _name );

		if ( _sElem == m_LeafNames.m_sLOD )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pLOD->FirstAttribute();

			//������ ������� ����� LOD'�
			DecodeAttrLod( _attr );

			//������� ������ � ��������
			DecodeVertexs( pLOD );
		}
	}
}

void xmlLeafLoad::DecodeAttrLod( TiXmlAttribute* _attr )
{
	double alfa = 0.0;

	//������ ������� ����� LOD'�
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_LeafNames.m_sNum )
			_attr->QueryIntValue( &m_iLOD );
		else
			if ( _sAttr == m_LeafNames.m_sAlfaTest )
				_attr->QueryDoubleValue( &alfa );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}

	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_fAlphaTestValue = alfa;
}

void xmlLeafLoad::DecodeVertexs( TiXmlElement* root )
{
	//������� ������ � ��������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sVertexs.c_str() );

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

void xmlLeafLoad::DecodePoints( TiXmlElement* root )
{
	//������� ������ � �����

	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_LeafNames.m_sPoint )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������������ �������� �����
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlLeafLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
{
	//������������ �������� �����
	double x , y , z;
	double nx , ny , nz;
	double s0 , t0 , p0 , q0;
	double s1 , t1 , p1;

	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
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

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}

	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vCoords.push_back( x );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vCoords.push_back( y );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vCoords.push_back( z );

	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vNormals.push_back( nx );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vNormals.push_back( ny );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vNormals.push_back( nz );

	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords0.push_back( s0 );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords0.push_back( t0 );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords0.push_back( p0 );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords0.push_back( q0 );

	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords1.push_back( s1 );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords1.push_back( t1 );
	m_pDataLeaf->m_vLfLOD[ m_iLOD ].m_vTexCoords1.push_back( p1 );
}

void xmlLeafLoad::DecodeWind( TiXmlElement* root )
{
	//������� ������ � ������� �����
	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_LeafNames.m_sWind.c_str() );

	if ( node )
	{
		TiXmlElement* pWind = node->ToElement();

		//������� ��� ��������
		const char *_name = pWind->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pWind->FirstAttribute();

		//������� �������� �����
		DecodeAttrWind( _attr );
	}
}

void xmlLeafLoad::DecodeAttrWind( TiXmlAttribute* _attr )
{
	double dFrqY = 0;
	double dFrqZ = 0;
	double dAmpY = 0;
	double dAmpZ = 0;
	//������� �������� �����
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_LeafNames.m_sFreqY )
			_attr->QueryDoubleValue( &dFrqY );
		else
			if ( _sAttr == m_LeafNames.m_sFreqZ )
				_attr->QueryDoubleValue( &dFrqZ );
			else
				if ( _sAttr == m_LeafNames.m_sAmplY )
					_attr->QueryDoubleValue( &dAmpY );
				else
					if ( _sAttr == m_LeafNames.m_sAmplZ )
						_attr->QueryDoubleValue( &dAmpZ );


		//��������� � ���������� ��������
		_attr = _attr->Next();
	}

	//�������� ��������� ��������
	m_pDataLeaf->m_fFreqY = dFrqY;
	m_pDataLeaf->m_fFreqZ = dFrqZ;
	m_pDataLeaf->m_fAmplY = dAmpY;
	m_pDataLeaf->m_fAmplZ = dAmpZ;
}