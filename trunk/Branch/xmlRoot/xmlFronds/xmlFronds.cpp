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
	//получить xml тег с сформированными данными
	xmlFrondsSave _save;

	return _save.GetXmlData();
}