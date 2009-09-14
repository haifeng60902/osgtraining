#ifndef _XML_FRONDS_SAVE_H_
#define _XML_FRONDS_SAVE_H_

#include "../../binData/dataFronds.h"
#include "../../tinyXML/tinyxml.h"

class xmlFrondsSave
{
public:
	xmlFrondsSave();
	~xmlFrondsSave();

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

private:
	//формирование записей LOD'ов
	void FillLODs( const dataFronds &_data , TiXmlElement* root );

	//заполнить данными о текстурах
	void FillTextures( const dataFronds &_data  , TiXmlElement* root );

	//заполнить данными о координатах
	void FillVertex( const dataFrLOD &_data  , TiXmlElement* root );

	//заполнить индексами
	void FillIndexes( const dataFrLOD &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_