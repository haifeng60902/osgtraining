#include "xmlBranchSave.h"

xmlBranchSave::xmlBranchSave() : m_pData( NULL )
{

}

xmlBranchSave::~xmlBranchSave()
{

}

ticpp::Node* xmlBranchSave::GetXmlData( const binBranch &_data )
{
	//�������� xml ��� � ��������������� �������
	m_pData = &_data;

	return NULL;
}
