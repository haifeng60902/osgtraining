#include "xmlFronds.h"

#include "xmlFrondsSave.h"

xmlFronds::xmlFronds()
{

}

xmlFronds::~xmlFronds()
{

}

TiXmlElement* xmlFronds::GetXmlData()
{
	//�������� xml ��� � ��������������� �������
	xmlFrondsSave _save;

	return _save.GetXmlData();
}