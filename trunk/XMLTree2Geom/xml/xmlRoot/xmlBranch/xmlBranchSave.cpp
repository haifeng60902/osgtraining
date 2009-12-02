#include "xmlBranchSave.h"

xmlBranchSave::xmlBranchSave() : m_pData( NULL )
{

}

xmlBranchSave::~xmlBranchSave()
{

}

ticpp::Node* xmlBranchSave::GetXmlData( const binBranch &_data )
{
	//получить xml тег с сформированными данными
	m_pData = &_data;

	return NULL;
}
