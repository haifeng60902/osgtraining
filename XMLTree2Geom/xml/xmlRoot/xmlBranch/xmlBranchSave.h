#ifndef _XML_BRANCH_SAVE_H_
#define _XML_BRANCH_SAVE_H_

#include "binBranch.h"
#include "ticpp.h"

class xmlBranchSave
{
public:
	xmlBranchSave();
	~xmlBranchSave();

	//получить xml тег с сформированными данными
	ticpp::Node* GetXmlData( const binBranch &_data );

};

#endif	//_XML_BRANCH_SAVE_H_