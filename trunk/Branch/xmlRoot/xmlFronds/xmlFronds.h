#ifndef _XML_FRONDS_H_
#define _XML_FRONDS_H_

#include "../../binData/dataFronds.h"
#include "../../tinyXML/tinyxml.h"

class xmlFronds
{
public:
	xmlFronds();
	~xmlFronds();

	//������������� ������
	void Init( TiXmlElement* root );

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

	//�������� ������ �� ������ �����
	dataFronds& GetDataFronds(){ return m_dataFronds; };

private:

	//�������� ������ � ������
	dataFronds m_dataFronds;
};

#endif	//_XML_FRONDS_H_