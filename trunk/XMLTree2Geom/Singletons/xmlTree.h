#ifndef _XML_TREE_H_
#define _XML_TREE_H_

#include "Singleton.h"
#include "ticpp.h"

#include "xmlTmpl.h"
#include "xmlBranch/xmlBranch.h"
#include "xmlFronds/xmlFronds.h"

#include <string>

class xmlTree : public Singleton< xmlTree >
{
public:
	xmlTree();
	~xmlTree();

	//�������������
	void Init( std::string _sFileName );

	//���������� ������
	void Close();

	//�������� ������ � ������ ������
	binBranch &GetBranch(){ return m_xmlBranch.GetData(); };

	//�������� ������ � ������ �����
	binFronds &GetFronds(){ return m_xmlFronds.GetData(); };

private:
	//���������������� �������� ������
	void InitChild( ticpp::Node* pNode );

	xmlTmpl< binBranch , xmlBranchLoad , xmlBranchSave > m_xmlBranch;	//������ � ������
	xmlTmpl< binFronds , xmlFrondsLoad , xmlFrondsSave > m_xmlFronds;	//������ � ������

	//��� ����� xml
	std::string m_sFileName;
};

#endif	//_XML_TREE_H_