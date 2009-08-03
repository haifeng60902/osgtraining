#ifndef _XML_ROOT_H_
#define _XML_ROOT_H_

#include "../binData/dataBranch.h"

#include "xmlBranch/xmlBranch.h"

#include "../Singleton.h"

class xmlRoot : public Singleton< xmlRoot >
{
public:
	xmlRoot();
	~xmlRoot();

	//�������� ������ �� ������ �����
	dataBranch& GetDataBranch(){ return m_xmlBranch.GetDataBranch(); };

	//������������� ������� xml ����������� ������
	void Init( std::string _name );

	//���������� ������ ������
	void Close();

private:

	//���������������� �������� ������
	void InitChild( TiXmlElement* root );

	//������ � ������
	xmlBranch m_xmlBranch;
};

#endif	//_XML_ROOT_H_