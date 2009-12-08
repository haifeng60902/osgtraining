#ifndef _XML_LEAF_LOAD_H_
#define _XML_LEAF_LOAD_H_

#include "binLeaf.h"
#include "ticpp.h"

class xmlLeafLoad
{
public:
	xmlLeafLoad();
	~xmlLeafLoad();

	//������ xml � ���������� �������� ������
	void ParseXml( ticpp::Node* pNode , binLeaf *_data );

private:
	//������� � ���� branch
	void DecodeSettings( ticpp::Node* pNode );

	//������� ����� �������
	void DecodeTextures( ticpp::Element* pTextures );

	//������� ������ LOD'��
	void DecodeLODs( ticpp::Element* pLODs );

	//������� ���������� �����
	void DecodePoint( ticpp::Element* pVertex , int i );

	//������� ���������� �������
	void DecodeVertex( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pVertex );

	//������� ���������� �������
	void DecodeNormal( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pNormal );

	//������� ���������� ����������
	void DecodeTexCoord( ticpp::Iterator< ticpp::Element > pPoint , tVecVertex *pTexCoord , tVecVertex *pVerOffset );

	binLeaf *m_pData;
};

#endif	//_XML_LEAF_LOAD_H_