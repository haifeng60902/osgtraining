#ifndef _XML_LEAF_SAVE_H_
#define _XML_LEAF_SAVE_H_

#include "../../binData/dataLeaf.h"
#include "../../tinyXML/tinyxml.h"

class xmlLeafSave
{
public:
	xmlLeafSave();
	~xmlLeafSave();

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

private:
	//��������� ������� � ���������
	void FillTextures( const dataLeaf &_data  , TiXmlElement* root );

	//������������ ������� LOD'��
	void FillLODs( const dataLeaf &_data , TiXmlElement* root );

	//��������� ������� � �����������
	void FillVertex( const dataLfLOD &_data  , TiXmlElement* root );

	//��������� ������� � �����
	void FillWind( TiXmlElement* root );
};

#endif	//_XML_LEAF_SAVE_H_