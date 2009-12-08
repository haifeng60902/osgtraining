#include "xmlLeafSave.h"

xmlLeafSave::xmlLeafSave() : m_pData( NULL )
{

}

xmlLeafSave::~xmlLeafSave()
{

}

ticpp::Node* xmlLeafSave::GetXmlData( const binLeaf &_data )
{
	//получить xml тег с сформированными данными
	m_pData = &_data;

	return NULL;
}
