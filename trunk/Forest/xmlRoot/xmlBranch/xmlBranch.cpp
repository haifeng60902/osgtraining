#include "xmlBranch.h"

#include "xmlBranchLoad.h"
#include "xmlBranchSave.h"

xmlBranch::xmlBranch()
{

}

xmlBranch::~xmlBranch()
{

}

void xmlBranch::Init( TiXmlElement* root )
{
	//инициализаци€ данных
	
	//создаем экземпл€р класса дл€ парсинга xml
	xmlBranchLoad _load;

	//разбор xml и заполнение бинарных данных
	_load.ParseXml( root  , &m_dataBranch );
}


TiXmlElement* xmlBranch::GetXmlData()
{
	//получить xml тег с сформированными данными
	xmlBranchSave _save;

	return _save.GetXmlData();
}