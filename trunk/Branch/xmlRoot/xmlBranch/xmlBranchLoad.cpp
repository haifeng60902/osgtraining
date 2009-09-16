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
	//������ xml � ���������� �������� ������
	
	m_pDataBranch = _data;

	//������� ������ � ������
	DecodeBranch( root );
}

void xmlBranchLoad::DecodeBranch( TiXmlElement* root )
{
	//������� ������ � ������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sBranch.c_str() );

	if ( node )
	{
		TiXmlElement* pBranch = node->ToElement();

		//������� ��� ��������
		const char *_name = pBranch->Value();
		std::string _sElem( _name );

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pBranch->FirstAttribute();

		//������������ �������� � ������ ��������
		DecodeAttrTexture( _attr );

		//������������ ������ LOD'��
		DecodeLODs( pBranch );
	}
}

void xmlBranchLoad::DecodeAttrTexture( TiXmlAttribute* _attr )
{
	//������������ �������� � ������ ��������
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sTexture )
			m_pDataBranch->m_sTexture = _attr->Value();

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeLODs( TiXmlElement* root )
{
	//������������ ������ LOD'��

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sLODs.c_str() );

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

void xmlBranchLoad::DecodeAttrNumLods( TiXmlAttribute* _attr )
{
	//������ ���������� LOD'��
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_BranchNames.m_sNum )
		{
			int iNum = 0;
			_attr->QueryIntValue( &iNum );

			m_pDataBranch->m_vLOD.resize( iNum );
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeLOD( TiXmlElement* root )
{
	//������������ ������ LOD'�

	for ( TiXmlElement *pLOD = root->FirstChildElement() ; pLOD ; pLOD = pLOD->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pLOD->Value();
		std::string _sElem( _name );

		if ( _sElem == m_BranchNames.m_sLOD )
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

void xmlBranchLoad::DecodeAttrLod( TiXmlAttribute* _attr )
{
	double alfa = 0.0;

	//������ ������� ����� LOD'�
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_BranchNames.m_sNum )
			_attr->QueryIntValue( &m_iLOD );
		else
			if ( _sAttr == m_BranchNames.m_sAlfaTest )
				_attr->QueryDoubleValue( &alfa );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}

	m_pDataBranch->m_vLOD[ m_iLOD ].m_fAlphaTestValue = alfa;
}

void xmlBranchLoad::DecodeVertexs( TiXmlElement* root )
{
	//������� ������ � ��������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sVertexs.c_str() );

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

void xmlBranchLoad::DecodePoints( TiXmlElement* root )
{
	//������� ������ � �����

	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sPoint )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������������ �������� �����
			DecodeAttrPoint( _attr );
		}
	}
}

void xmlBranchLoad::DecodeAttrPoint( TiXmlAttribute* _attr )
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

		//��������� � ���������� ��������
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
	//������� ������ � ��������

	//���������� ���������� �� ���� XML
	TiXmlNode* node = root->FirstChild( m_BranchNames.m_sStrips.c_str() );

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

void xmlBranchLoad::DecodeAttrNumStrips( TiXmlAttribute* _attr )
{
	//������� ���������� �������

	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_BranchNames.m_sNum )
		{
			int num;
			_attr->QueryIntValue( &num );
			m_pDataBranch->m_vLOD[ m_iLOD ].m_Strips.resize( num );
		}

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
}

void xmlBranchLoad::DecodeStrip( TiXmlElement* root )
{
	//������������ �������

	int ind = 0;
	//������� ���� ���������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sStrip )
		{
			//������������ �������
			DecodeInd( pElem , ind );
			
			++ind;
		}
	}
}

void xmlBranchLoad::DecodeInd( TiXmlElement* root , int ind )
{
//������������ �������
	for ( TiXmlElement *pElem = root->FirstChildElement() ; pElem ; pElem = pElem->NextSiblingElement() )
	{
		//������� ��� ��������
		const char *_name = pElem->Value();
		std::string _sAttr( _name );

		if ( _sAttr == m_BranchNames.m_sInd )
		{
			//�������� ��������� �� ������ ������� ��������
			TiXmlAttribute* _attr = pElem->FirstAttribute();

			//������� ��������� ������
			int i = DecodeAttrInd( _attr );
			m_pDataBranch->m_vLOD[ m_iLOD ].m_Strips[ ind ].push_back( i );
		}
	}
}

int xmlBranchLoad::DecodeAttrInd( TiXmlAttribute* _attr )
{
	//������� ��������� ������
	int ind = 0;
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_BranchNames.m_sVal )
			_attr->QueryIntValue( &ind );

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
	return ind;
}
