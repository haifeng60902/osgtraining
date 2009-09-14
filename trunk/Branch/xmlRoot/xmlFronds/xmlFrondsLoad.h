#ifndef _XML_FRONDS_LOAD_H_
#define _XML_FRONDS_LOAD_H_

#include "../../binData/dataFronds.h"

#include "../../tinyXML/tinyxml.h"

class xmlFrondsLoad
{
public:
	xmlFrondsLoad();
	~xmlFrondsLoad();

	//������ xml � ���������� �������� ������ � ������
	void ParseXml( TiXmlElement* root , dataFronds *_data );

private:

	//������� ������ � ������
	void DecodeFronds( TiXmlElement* root );

	//������������ �������� ��� ����� �����
	void DecodeAttrAlfa( TiXmlAttribute* _attr );

	//������� ������ � ���������
	void DecodeTextures( TiXmlElement* root );

	//������� ������ � ��������
	void DecodeTexture( TiXmlElement* root );

	//������������ ������� ��� ��������
	void DecodeAttrTexture( TiXmlAttribute* _attr );

	//������������ ������ LOD'��
	void DecodeLODs( TiXmlElement* root );

	//������ ���������� LOD'��
	void DecodeAttrNumLods( TiXmlAttribute* _attr );

	//������������ ������ LOD'�
	void DecodeLOD( TiXmlElement* root );

	//������ ������� ����� LOD'�
	void DecodeAttrLod( TiXmlAttribute* _attr );

	//������� ������ � ��������
	void DecodeVertexs( TiXmlElement* root );

	//������� ������ � �����
	void DecodePoints( TiXmlElement* root );

	//������������ �������� �����
	void DecodeAttrPoint( TiXmlAttribute* _attr );

	//������� ������ � ��������
	void DecodeStrips( TiXmlElement* root );

	//������� ���������� �������
	void DecodeAttrNumStrips( TiXmlAttribute* _attr );

	//������������ �������
	void DecodeStrip( TiXmlElement* root );

	//������������ �������
	void DecodeInd( TiXmlElement* root , int ind );

	//������� ��������� ������
	int DecodeAttrInd( TiXmlAttribute* _attr );

	dataFronds *m_pDataFronds;

	//����� �������� ��������������� LOD'�
	int m_iLOD;
};

#endif	//_XML_BRANCH_LOAD_H_