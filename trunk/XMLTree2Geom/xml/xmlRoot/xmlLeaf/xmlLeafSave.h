#ifndef _XML_LEAF_SAVE_H_
#define _XML_LEAF_SAVE_H_

#include "binLeaf.h"
#include "ticpp.h"

class xmlLeafSave
{
public:
	xmlLeafSave();
	~xmlLeafSave();

	//получить xml тег с сформированными данными
	ticpp::Node* GetXmlData( const binLeaf &_data );

private:
	const binLeaf *m_pData;
};

#endif	//_XML_LEAF_SAVE_H_