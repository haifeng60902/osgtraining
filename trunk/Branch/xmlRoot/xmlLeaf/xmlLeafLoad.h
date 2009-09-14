#ifndef _XML_LEAF_LOAD_H_
#define _XML_LEAF_LOAD_H_

#include "../../binData/dataLeaf.h"

#include "../../tinyXML/tinyxml.h"

class xmlLeafLoad
{
public:
	xmlLeafLoad();
	~xmlLeafLoad();

	//разбор xml и заполнение бинарных данных о листве
	void ParseXml( TiXmlElement* root , dataLeaf *_data );

private:

	//извлечь данные о листве
	void DecodeLeaf( TiXmlElement* root );

	//извлечь данные о текстурах
	void DecodeTextures( TiXmlElement* root );

	//извлечь данные о текстуре
	void DecodeTexture( TiXmlElement* root );

	//декодировать атрибут имя текстуры
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

	//извлечь данные о влиянии ветра
	void DecodeWind( TiXmlElement* root );

	//извлечь атрибуты ветра
	void DecodeAttrWind( TiXmlAttribute* _attr );

	dataLeaf *m_pDataLeaf;

	//номер текущего обрабатываемого LOD'а
	int m_iLOD;
};

#endif	//_XML_LEAF_LOAD_H_