#ifndef _XML_LEAF_SAVE_H_
#define _XML_LEAF_SAVE_H_

#include "../../binData/dataLeaf.h"
#include "../../tinyXML/tinyxml.h"

class xmlLeafSave
{
public:
	xmlLeafSave();
	~xmlLeafSave();

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

private:
	//заполнить данными о текстурах
	void FillTextures( const dataLeaf &_data  , TiXmlElement* root );

	//формирование записей LOD'ов
	void FillLODs( const dataLeaf &_data , TiXmlElement* root );

	//заполнить данными о координатах
	void FillVertex( const dataLfLOD &_data  , TiXmlElement* root );

	//заполнить данными о ветре
	void FillWind( TiXmlElement* root );
};

#endif	//_XML_LEAF_SAVE_H_