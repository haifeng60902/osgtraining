#ifndef _XML_LEAF_H_
#define _XML_LEAF_H_

#include "../../binData/dataLeaf.h"
#include "../../tinyXML/tinyxml.h"

class xmlLeaf
{
public:
	xmlLeaf();
	~xmlLeaf();

	//инициализация данных
	void Init( TiXmlElement* root );

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

	//получить ссылку на данные веток
	dataLeaf& GetDataLeaf(){ return m_dataLeaf; };

private:

	//бинарные данные о листве
	dataLeaf m_dataLeaf;
};

#endif	//_XML_LEAF_H_