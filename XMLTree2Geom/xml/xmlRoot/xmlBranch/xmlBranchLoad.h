#ifndef _XML_BRANCH_LOAD_H_
#define _XML_BRANCH_LOAD_H_

#include "binBranch.h"
#include "ticpp.h"

class xmlBranchLoad
{
public:
	xmlBranchLoad();
	~xmlBranchLoad();

	//разбор xml и заполнение бинарных данных
	void ParseXml( ticpp::Node* pNode , binBranch *_data );

private:
	//перейти к узлу branch
	void DecodeSettings( ticpp::Node* pNode );

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

	binBranch *m_pData;
};

#endif	//_XML_BRANCH_LOAD_H_