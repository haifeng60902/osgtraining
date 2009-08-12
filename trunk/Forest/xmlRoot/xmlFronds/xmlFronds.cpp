#include "xmlFronds.h"

#include "xmlFrondsLoad.h"
#include "xmlFrondsSave.h"

xmlFronds::xmlFronds()
{

}

xmlFronds::~xmlFronds()
{

}

void xmlFronds::Init( TiXmlElement* root )
{
	//������������� ������ �����

	//������� ��������� ������ ��� �������� xml
	xmlFrondsLoad _load;

	//������ xml � ���������� �������� ������
	_load.ParseXml( root  , &m_dataFronds );
}

TiXmlElement* xmlFronds::GetXmlData()
{
	//�������� xml ��� � ��������������� �������
	xmlFrondsSave _save;

	return _save.GetXmlData();
}