#ifndef _XML_LEAF_LOAD_H_
#define _XML_LEAF_LOAD_H_

#include "binLeaf.h"
#include "ticpp.h"

class xmlLeafLoad
{
public:
	xmlLeafLoad();
	~xmlLeafLoad();

	//разбор xml и заполнение бинарных данных
	void ParseXml( ticpp::Node* pNode , binLeaf *_data );

private:
	//перейти к узлу branch
	void DecodeSettings( ticpp::Node* pNode );

	//извлечь имена текстур
	void DecodeTextures( ticpp::Element* pTextures );

	//считать данные LOD'ов
	void DecodeLODs( ticpp::Element* pLODs );

	//считать координаты точки
	void DecodePoint( ticpp::Element* pVertex , int i );

	//извлечь координаты вершины
	void DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pVertex );

	//извлечь координаты нормали
	void DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pNormal );

	//извлечь текстурные координаты
	void DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pTexCoord , tVecVertex *pVerOffset );

	binLeaf *m_pData;
};

#endif	//_XML_LEAF_LOAD_H_