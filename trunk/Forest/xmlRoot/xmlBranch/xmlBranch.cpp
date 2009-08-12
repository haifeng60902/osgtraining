#include "xmlBranch.h"

#include "xmlBranchLoad.h"
#include "xmlBranchSave.h"

xmlBranch::xmlBranch()
{

}

xmlBranch::~xmlBranch()
{

}

void xmlBranch::Init( TiXmlElement* root )
{
	//������������� ������
	
	//������� ��������� ������ ��� �������� xml
	xmlBranchLoad _load;

	//������ xml � ���������� �������� ������
	_load.ParseXml( root  , &m_dataBranch );
}


TiXmlElement* xmlBranch::GetXmlData()
{
	//�������� xml ��� � ��������������� �������
	xmlBranchSave _save;

	return _save.GetXmlData();
}