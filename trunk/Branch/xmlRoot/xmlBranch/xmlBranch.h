#ifndef _XML_BRANCH_H_
#define _XML_BRANCH_H_

#include "../../binData/dataBranch.h"

#include "../../tinyXML/tinyxml.h"

class xmlBranch
{
public:
	xmlBranch();
	~xmlBranch();

	//������������� ������
	void Init( TiXmlElement* root );

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData();

	//�������� ������ �� ������ �����
	dataBranch& GetDataBranch(){ return m_dataBranch; };

private:
	//�������� ������ � ������
	dataBranch m_dataBranch;

};

#endif	//_XML_BRANCH_H_