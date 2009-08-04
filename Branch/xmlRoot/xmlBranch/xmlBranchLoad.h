#ifndef _XML_BRANCH_LOAD_H_
#define _XML_BRANCH_LOAD_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranchLoad
{
public:
	xmlBranchLoad();
	~xmlBranchLoad();

	//разбор xml и заполнение бинарных данных о антмосфере
	void ParseXml( TiXmlElement* root , dataBranch *_data );

private:

	//извлечь данные о стволе
	void DecodeBranch( TiXmlElement* root );

	//декодировать параметр для альфа теста
	void DecodeAttrAlfa( TiXmlAttribute* _attr );

	//извлечь данные о вершинах
	void DecodeVertexs( TiXmlElement* root );

	//извлечь данные о точке
	void DecodePoints( TiXmlElement* root );

	//декодировать параметр точки
	void DecodeAttrPoint( TiXmlAttribute* _attr );

	//извлечь данные о индексах
	void DecodeStrips( TiXmlElement* root );

	//извлечь количество полосок
	void DecodeAttrNumStrips( TiXmlAttribute* _attr );

	//декодировать полоски
	void DecodeStrip( TiXmlElement* root );

	//декодировать индексы
	void DecodeInd( TiXmlElement* root , int ind );

	//извлечь очередной индекс
	int DecodeAttrInd( TiXmlAttribute* _attr );

	dataBranch *m_pDataBranch;

};

#endif	//_XML_BRANCH_LOAD_H_