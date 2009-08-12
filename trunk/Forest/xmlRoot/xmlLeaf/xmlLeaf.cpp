#include "xmlLeaf.h"

#include "xmlLeafLoad.h"
#include "xmlLeafSave.h"

xmlLeaf::xmlLeaf()
{

}

xmlLeaf::~xmlLeaf()
{

}

void xmlLeaf::Init( TiXmlElement* root )
{
	//������������� ������ �����

	//������� ��������� ������ ��� �������� xml
	xmlLeafLoad _load;

	//������ xml � ���������� �������� ������
	_load.ParseXml( root  , &m_dataLeaf );
}

TiXmlElement* xmlLeaf::GetXmlData()
{
	//�������� xml ��� � ��������������� �������
	xmlLeafSave _save;

	return _save.GetXmlData();
}