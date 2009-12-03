#ifndef _XML_BRANCH_LOAD_H_
#define _XML_BRANCH_LOAD_H_

#include "binBranch.h"
#include "ticpp.h"

class xmlBranchLoad
{
public:
	xmlBranchLoad();
	~xmlBranchLoad();

	//������ xml � ���������� �������� ������
	void ParseXml( ticpp::Node* pNode , binBranch *_data );

private:
	//������� � ���� branch
	void DecodeSettings( ticpp::Node* pNode );

	//������� ������ LOD'��
	void DecodeLODs( ticpp::Element* pLODs );

	//������� ���������� �����
	void DecodePoint( ticpp::Element* pVertex , int i );

	binBranch *m_pData;
};

#endif	//_XML_BRANCH_LOAD_H_