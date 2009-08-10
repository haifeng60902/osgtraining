#include "xmlLeaf.h"

#include "xmlLeafLoad.h"
#include "xmlLeafSave.h"

xmlLeaf::xmlLeaf()
{

}

xmlLeaf::~xmlLeaf()
{

}

void xmlLeaf::Init( TiXmlElement* root )
{
	//инициализаци€ данных веток

	//создаем экземпл€р класса дл€ парсинга xml
	xmlLeafLoad _load;

	//разбор xml и заполнение бинарных данных
	_load.ParseXml( root  , &m_dataLeaf );
}

TiXmlElement* xmlLeaf::GetXmlData()
{
	//получить xml тег с сформированными данными
	xmlLeafSave _save;

	return _save.GetXmlData();
}