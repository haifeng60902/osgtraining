#include "xmlFrondsSave.h"

xmlFrondsSave::xmlFrondsSave() : m_pData( NULL )
{

}

xmlFrondsSave::~xmlFrondsSave()
{

}

ticpp::Node* xmlFrondsSave::GetXmlData( const binFronds &_data )
{
	//получить xml тег с сформированными данными
	m_pData = &_data;

	return NULL;
}
