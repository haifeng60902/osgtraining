#ifndef _XML_FRONDS_H_
#define _XML_FRONDS_H_

#include "../../binData/dataFronds.h"
#include "../../tinyXML/tinyxml.h"

class xmlFronds
{
public:
	xmlFronds();
	~xmlFronds();

	//инициализация данных
	void Init( TiXmlElement* root );

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

	//получить ссылку на данные веток
	dataFronds& GetDataFronds(){ return m_dataFronds; };

private:

	//бинарные данные о ветках
	dataFronds m_dataFronds;
};

#endif	//_XML_FRONDS_H_