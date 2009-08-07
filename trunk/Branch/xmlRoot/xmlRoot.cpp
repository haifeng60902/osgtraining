#include "xmlRoot.h"

xmlRoot::xmlRoot()
{

}

xmlRoot::~xmlRoot()
{

}

void xmlRoot::Init( std::string _name )
{
	//������������� ������� xml ����������� ������

	//������������� ������� xml
	TiXmlDocument doc( _name.c_str() );

	bool loadOkay = doc.LoadFile( TIXML_ENCODING_LEGACY );
	if ( !loadOkay )
	{
		char buf[255];
		sprintf_s( buf , "Could not load test file 'settings.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( -1 );
	}

	TiXmlElement* root;
	root = doc.RootElement();

	//���������������� �������� ������
	InitChild( root );
}

void xmlRoot::InitChild( TiXmlElement* root )
{
	//���������������� �������� ������

	//���������������� ������ ������
	m_xmlBranch.Init( root );

	//���������������� ������ �����
	m_xmlFronds.Init( root );
}

void xmlRoot::Close()
{
	//���������� ������ ������

	//��������� ��������� � settings.xml
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild( decl );

	//������� �������� ���� visual
	TiXmlElement* pRoot = NULL;
	pRoot = new TiXmlElement( "root" );

	//��������� ���� branch
	pRoot->LinkEndChild( m_xmlBranch.GetXmlData() );

	//��������� ���� fronds
	pRoot->LinkEndChild( m_xmlFronds.GetXmlData() );

	doc.LinkEndChild( pRoot );	

	//��������� ������ � ����
	doc.SaveFile( "tree.xml" );
}