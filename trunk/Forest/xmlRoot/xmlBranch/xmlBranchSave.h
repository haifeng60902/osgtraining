#ifndef _XML_BRANCH_SAVE_H_
#define _XML_BRANCH_SAVE_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranchSave
{
public:
	xmlBranchSave();
	~xmlBranchSave();

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

private:
	//��������� ������� � �����������
	void FillVertex( const dataBranch &_data  , TiXmlElement* root );

	//��������� ���������
	void FillIndexes( const dataBranch &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_