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

		//������������ �������� ��� ����� �����
		DecodeAttrAlfa( _attr );

		//������� ������ � ��������
		DecodeVertexs( pBranch );

		//������� ������ � ��������
		DecodeStrips( pBranch );
	}
}

void xmlBranchLoad::DecodeAttrAlfa( TiXmlAttribute* _attr )
{
	//������������ �������� ��� ����� �����
	while ( _attr )
	{
		//��� ��������
		const char *_name = _attr->Name();
		std::string _sAttr( _name );

		//��������� ��������
		if ( _sAttr == m_BranchNames.m_sAlfaTest )
		{
			double alfa = 0.0;
			_attr->QueryDoubleValue( &alfa );

			m_pDataBranch->m_fAlphaTestValue = alfa;
		}
		else
			if ( _sAttr == m_BranchNames.m_sTexture )
				m_pDataBranch->m_sTexture = _attr->Value();

		//��������� � ���������� ��������
		_attr = _attr->Next();
	}
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

		//�������� ��������� �� ������ ������� ��������
		TiXmlAttribute* _attr = pElem->FirstAttribute();

		//������������ �������� �����
		DecodeAttrPoint( _attr );
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
			m_pDataBranch->m_Strips.resize( num );
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
			m_pDataBranch->m_Strips[ ind ].push_back( i );
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
