#include "xmlFrondsSave.h"

xmlFrondsSave::xmlFrondsSave() : m_pData( NULL )
{

}

xmlFrondsSave::~xmlFrondsSave()
{

}

ticpp::Node* xmlFrondsSave::GetXmlData( const binFronds &_data )
{
	//�������� xml ��� � ��������������� �������
	m_pData = &_data;

	return NULL;
}
