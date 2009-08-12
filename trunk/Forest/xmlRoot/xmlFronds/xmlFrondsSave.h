#ifndef _XML_FRONDS_SAVE_H_
#define _XML_FRONDS_SAVE_H_

#include "../../binData/dataFronds.h"
#include "../../tinyXML/tinyxml.h"

class xmlFrondsSave
{
public:
	xmlFrondsSave();
	~xmlFrondsSave();

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

private:
	//��������� ������� � ���������
	void FillTextures( const dataFronds &_data  , TiXmlElement* root );

	//��������� ������� � �����������
	void FillVertex( const dataFronds &_data  , TiXmlElement* root );

	//��������� ���������
	void FillIndexes( const dataFronds &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_