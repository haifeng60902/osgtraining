#ifndef _XML_ROOT_H_
#define _XML_ROOT_H_

#include "xmlBranch/xmlBranch.h"
#include "xmlFronds/xmlFronds.h"
#include "xmlLeaf/xmlLeaf.h"

#include "../Singleton.h"

class xmlRoot : public Singleton< xmlRoot >
{
public:
	xmlRoot();
	~xmlRoot();

	//�������� ������ �� ������ ������
	dataBranch& GetDataBranch(){ return m_xmlBranch.GetDataBranch(); };

	//�������� ������ �� ������ �����
	dataFronds& GetDataFronds(){ return m_xmlFronds.GetDataFronds(); };

	//�������� ������ �� ������ ������
	dataLeaf& GetDataLeaf(){ return m_xmlLeaf.GetDataLeaf(); };

	//������������� ������� xml ����������� ������
	void Init( std::string _name );

	//���������� ������ ������
	void Close();

private:

	//���������������� �������� ������
	void InitChild( TiXmlElement* root );

	//������ � ������
	xmlBranch m_xmlBranch;

	//������ � ������
	xmlFronds m_xmlFronds;

	//������ � ������
	xmlLeaf m_xmlLeaf;
};

#endif	//_XML_ROOT_H_