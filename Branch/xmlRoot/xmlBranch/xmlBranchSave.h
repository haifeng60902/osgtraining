#ifndef _XML_BRANCH_SAVE_H_
#define _XML_BRANCH_SAVE_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranchSave
{
public:
	xmlBranchSave();
	~xmlBranchSave();

	//получить xml тег с сформированными данными
	TiXmlElement* GetXmlData();

private:
	//формирование записей LOD'ов
	void FillLODs( const dataBranch &_data  , TiXmlElement* root );

	//заполнить данными о координатах
	void FillVertex( const dataLOD &_data  , TiXmlElement* root );

	//заполнить индексами
	void FillIndexes( const dataLOD &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_