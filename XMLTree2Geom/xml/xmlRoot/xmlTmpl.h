#ifndef _XML_TMPL_H_
#define _XML_TMPL_H_

#include "ticpp.h"

template < class Bin , class Load , class Save >
class xmlTmpl
{
public:
	xmlTmpl(){};
	~xmlTmpl(){};

	//инициализаци€ данных
	void Init( ticpp::Node* pNode )
	{
		//создаем экземпл€р класса дл€ парсинга xml
		Load _load;

		//разбор xml и заполнение бинарных данных
		_load.ParseXml( pNode , &m_Data );
	};

	//получить xml тег с сформированными данными
	ticpp::Node* GetXmlData()
	{
		//получить xml тег с сформированными данными
		Save _save;

		return _save.GetXmlData( m_Data );
	};

	//получить ссылку на данные
	Bin& GetData(){ return m_Data; };

private:
	Bin m_Data;
};

#endif	//_XML_TMPL_H_