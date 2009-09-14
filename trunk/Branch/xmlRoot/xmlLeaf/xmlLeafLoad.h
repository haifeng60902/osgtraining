#ifndef _XML_LEAF_LOAD_H_
#define _XML_LEAF_LOAD_H_

#include "../../binData/dataLeaf.h"

#include "../../tinyXML/tinyxml.h"

class xmlLeafLoad
{
public:
	xmlLeafLoad();
	~xmlLeafLoad();

	//������ xml � ���������� �������� ������ � ������
	void ParseXml( TiXmlElement* root , dataLeaf *_data );

private:

	//������� ������ � ������
	void DecodeLeaf( TiXmlElement* root );

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

	//������� ������ � ������� �����
	void DecodeWind( TiXmlElement* root );

	//������� �������� �����
	void DecodeAttrWind( TiXmlAttribute* _attr );

	dataLeaf *m_pDataLeaf;

	//����� �������� ��������������� LOD'�
	int m_iLOD;
};

#endif	//_XML_LEAF_LOAD_H_