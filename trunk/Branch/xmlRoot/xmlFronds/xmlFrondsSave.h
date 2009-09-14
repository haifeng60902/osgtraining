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
	//������������ ������� LOD'��
	void FillLODs( const dataFronds &_data , TiXmlElement* root );

	//��������� ������� � ���������
	void FillTextures( const dataFronds &_data  , TiXmlElement* root );

	//��������� ������� � �����������
	void FillVertex( const dataFrLOD &_data  , TiXmlElement* root );

	//��������� ���������
	void FillIndexes( const dataFrLOD &_data  , TiXmlElement* root );

};

#endif	//_XML_BRANCH_SAVE_H_