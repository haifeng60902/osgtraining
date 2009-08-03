#ifndef _XML_ROOT_H_
#define _XML_ROOT_H_

#include "../binData/dataBranch.h"

#include "xmlBranch/xmlBranch.h"

#include "../Singleton.h"

class xmlRoot : public Singleton< xmlRoot >
{
public:
	xmlRoot();
	~xmlRoot();

	//получить ссылку на данные веток
	dataBranch& GetDataBranch(){ return m_xmlBranch.GetDataBranch(); };

	//инициализация разбора xml содержащего данные
	void Init( std::string _name );

	//завершение работы класса
	void Close();

private:

	//инициализировать дочерние данные
	void InitChild( TiXmlElement* root );

	//данные о стволе
	xmlBranch m_xmlBranch;
};

#endif	//_XML_ROOT_H_