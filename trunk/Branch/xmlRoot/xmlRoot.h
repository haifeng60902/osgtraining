#ifndef _XML_ROOT_H_
#define _XML_ROOT_H_

#include "xmlBranch/xmlBranch.h"
#include "xmlFronds/xmlFronds.h"
#include "xmlLeaf/xmlLeaf.h"

#include "../Singleton.h"

class xmlRoot : public Singleton< xmlRoot >
{
public:
	xmlRoot();
	~xmlRoot();

	//получить ссылку на данные ствола
	dataBranch& GetDataBranch(){ return m_xmlBranch.GetDataBranch(); };

	//получить ссылку на данные веток
	dataFronds& GetDataFronds(){ return m_xmlFronds.GetDataFronds(); };

	//получить ссылку на данные листвы
	dataLeaf& GetDataLeaf(){ return m_xmlLeaf.GetDataLeaf(); };

	//инициализация разбора xml содержащего данные
	void Init( std::string _name );

	//завершение работы класса
	void Close();

private:

	//инициализировать дочерние данные
	void InitChild( TiXmlElement* root );

	//данные о стволе
	xmlBranch m_xmlBranch;

	//данные о ветках
	xmlFronds m_xmlFronds;

	//данные о листве
	xmlLeaf m_xmlLeaf;
};

#endif	//_XML_ROOT_H_