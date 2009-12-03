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

	binBranch *m_pData;
};

#endif	//_XML_BRANCH_LOAD_H_