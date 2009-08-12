#ifndef _XML_BRANCH_H_
#define _XML_BRANCH_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranch
{
public:
	xmlBranch();
	~xmlBranch();

	//инициализация данных
	void Init( TiXmlElement* root );

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

	//получить ссылку на данные веток
	dataBranch& GetDataBranch(){ return m_dataBranch; };

private:
	//бинарные данные о стволе
	dataBranch m_dataBranch;

};

#endif	//_XML_BRANCH_H_