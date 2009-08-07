#include "xmlRoot.h"

xmlRoot::xmlRoot()
{

}

xmlRoot::~xmlRoot()
{

}

void xmlRoot::Init( std::string _name )
{
	//инициализация разбора xml содержащего данные

	//инициализация разбора xml
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

	//инициализировать дочерние данные
	InitChild( root );
}

void xmlRoot::InitChild( TiXmlElement* root )
{
	//инициализировать дочерние данные

	//инициализировать данные ствола
	m_xmlBranch.Init( root );

	//инициализировать данные веток
	m_xmlFronds.Init( root );
}

void xmlRoot::Close()
{
	//завершение работы класса

	//сохранить параметры в settings.xml
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild( decl );

	//создаем корневой узел visual
	TiXmlElement* pRoot = NULL;
	pRoot = new TiXmlElement( "root" );

	//добавляем узел branch
	pRoot->LinkEndChild( m_xmlBranch.GetXmlData() );

	//добавляем узел fronds
	pRoot->LinkEndChild( m_xmlFronds.GetXmlData() );

	doc.LinkEndChild( pRoot );	

	//сохранить данные в файл
	doc.SaveFile( "tree.xml" );
}