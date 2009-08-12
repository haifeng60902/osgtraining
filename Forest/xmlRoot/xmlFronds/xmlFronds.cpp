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
	//инициализаци€ данных веток

	//создаем экземпл€р класса дл€ парсинга xml
	xmlFrondsLoad _load;

	//разбор xml и заполнение бинарных данных
	_load.ParseXml( root  , &m_dataFronds );
}

TiXmlElement* xmlFronds::GetXmlData()
{
	//получить xml тег с сформированными данными
	xmlFrondsSave _save;

	return _save.GetXmlData();
}