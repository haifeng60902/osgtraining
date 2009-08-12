#ifndef _XML_LEAF_H_
#define _XML_LEAF_H_

#include "../../binData/dataLeaf.h"
#include "../../tinyXML/tinyxml.h"

class xmlLeaf
{
public:
	xmlLeaf();
	~xmlLeaf();

	//������������� ������
	void Init( TiXmlElement* root );

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

	//�������� ������ �� ������ �����
	dataLeaf& GetDataLeaf(){ return m_dataLeaf; };

private:

	//�������� ������ � ������
	dataLeaf m_dataLeaf;
};

#endif	//_XML_LEAF_H_