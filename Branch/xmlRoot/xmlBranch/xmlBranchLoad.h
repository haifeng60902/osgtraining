#ifndef _XML_BRANCH_LOAD_H_
#define _XML_BRANCH_LOAD_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranchLoad
{
public:
	xmlBranchLoad();
	~xmlBranchLoad();

	//разбор xml и заполнение бинарных данных о стволе
	void ParseXml( TiXmlElement* root , dataBranch *_data );

private:

	//извлечь данные о стволе
	void DecodeBranch( TiXmlElement* root );

	//декодировать параметр с именем текстуры
	void DecodeAttrTexture( TiXmlAttribute* _attr );

	//декодировать данные LOD'ов
	void DecodeLODs( TiXmlElement* root );

	//узнать количество LOD'ов
	void DecodeAttrNumLods( TiXmlAttribute* _attr );

	//декодировать данные LOD'а
	void DecodeLOD( TiXmlElement* root );

	//узнать текущий номер LOD'а
	void DecodeAttrLod( TiXmlAttribute* _attr );

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

	//номер текущего обрабатываемого LOD'а
	int m_iLOD;

};

#endif	//_XML_BRANCH_LOAD_H_