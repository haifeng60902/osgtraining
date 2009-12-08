#ifndef _XML_FRONDS_LOAD_H_
#define _XML_FRONDS_LOAD_H_

#include "binFronds.h"
#include "ticpp.h"

class xmlFrondsLoad
{
public:
	xmlFrondsLoad();
	~xmlFrondsLoad();

	//разбор xml и заполнение бинарных данных
	void ParseXml( ticpp::Node* pNode , binFronds *_data );

private:
	//перейти к узлу branch
	void DecodeSettings( ticpp::Node* pNode );

	//извлечь имена текстур
	void DecodeTextures( ticpp::Element* pTextures );

	//считать данные LOD'ов
	void DecodeLODs( ticpp::Element* pLODs );

	//считать координаты точки
	void DecodePoint( ticpp::Element* pVertex , int i );

	//считать индексы
	void DecodeStrips( ticpp::Element* pStrips , int i );

	//извлечь координаты вершины
	void DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pVertex );

	//извлечь координаты нормали
	void DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pNormal );

	//извлечь текстурные координаты
	void DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pTexCoord );

	binFronds *m_pData;
};

#endif	//_XML_FRONDS_LOAD_H_