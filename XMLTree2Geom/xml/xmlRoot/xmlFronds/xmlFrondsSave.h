#ifndef _XML_FRONDS_SAVE_H_
#define _XML_FRONDS_SAVE_H_

#include "binFronds.h"
#include "ticpp.h"

class xmlFrondsSave
{
public:
	xmlFrondsSave();
	~xmlFrondsSave();

	//получить xml тег с сформированными данными
	ticpp::Node* GetXmlData( const binFronds &_data );

private:
	const binFronds *m_pData;
};

#endif	//_XML_FRONDS_SAVE_H_