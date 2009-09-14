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
	//������������ ������� LOD'��
	void FillLODs( const dataBranch &_data  , TiXmlElement* root );

	//��������� ������� � �����������
	void FillVertex( const dataLOD &_data  , TiXmlElement* root );

	//��������� ���������
	void FillIndexes( const dataLOD &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_