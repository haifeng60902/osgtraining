#ifndef _XML_BRANCH_SAVE_H_
#define _XML_BRANCH_SAVE_H_

#include "binBranch.h"
#include "ticpp.h"

class xmlBranchSave
{
public:
	xmlBranchSave();
	~xmlBranchSave();

	//�������� xml ��� � ��������������� �������
	ticpp::Node* GetXmlData( const binBranch &_data );

};

#endif	//_XML_BRANCH_SAVE_H_