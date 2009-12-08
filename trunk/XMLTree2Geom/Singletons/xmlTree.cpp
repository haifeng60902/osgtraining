#include "xmlTree.h"

#include <iostream>

xmlTree::xmlTree()
{

}

xmlTree::~xmlTree()
{

}

void xmlTree::Init( std::string _sFileName )
{
	//�������������
	m_sFileName = _sFileName;

	//
	try
	{
		// Load a document
		ticpp::Document doc( "tree.xml" );
		doc.LoadFile();

		//���������������� �������� ������
		InitChild( doc.FirstChildElement() );
	}
	catch( ticpp::Exception& ex )
	{
		// If any function has an error, execution will enter here.
		// Report the error
		std::cout << ex.what();
	}
}

void xmlTree::InitChild( ticpp::Node* pNode )
{
	//���������������� �������� ������
	m_xmlBranch.Init( pNode );
	m_xmlFronds.Init( pNode );
	m_xmlLeaf.Init( pNode );
}