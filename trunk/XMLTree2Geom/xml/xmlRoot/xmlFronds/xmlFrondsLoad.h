#ifndef _XML_FRONDS_LOAD_H_
#define _XML_FRONDS_LOAD_H_

#include "binFronds.h"
#include "ticpp.h"

class xmlFrondsLoad
{
public:
	xmlFrondsLoad();
	~xmlFrondsLoad();

	//������ xml � ���������� �������� ������
	void ParseXml( ticpp::Node* pNode , binFronds *_data );

private:
	//������� � ���� branch
	void DecodeSettings( ticpp::Node* pNode );

	//������� ����� �������
	void DecodeTextures( ticpp::Element* pTextures );

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

	binFronds *m_pData;
};

#endif	//_XML_FRONDS_LOAD_H_