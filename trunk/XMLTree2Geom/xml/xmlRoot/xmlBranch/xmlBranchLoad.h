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

	//������� �������
	void DecodeStrips( ticpp::Element* pStrips , int i );

	//������� ���������� �������
	void DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pVertex );

	//������� ���������� �������
	void DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pNormal );

	//������� ���������� ����������
	void DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pTexCoord );

	binBranch *m_pData;
};

#endif	//_XML_BRANCH_LOAD_H_