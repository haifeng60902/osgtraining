#ifndef _XML_BRANCH_LOAD_H_
#define _XML_BRANCH_LOAD_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranchLoad
{
public:
	xmlBranchLoad();
	~xmlBranchLoad();

	//������ xml � ���������� �������� ������ � ����������
	void ParseXml( TiXmlElement* root , dataBranch *_data );

private:

	//������� ������ � ������
	void DecodeBranch( TiXmlElement* root );

	//������������ �������� ��� ����� �����
	void DecodeAttrAlfa( TiXmlAttribute* _attr );

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

	dataBranch *m_pDataBranch;

};

#endif	//_XML_BRANCH_LOAD_H_