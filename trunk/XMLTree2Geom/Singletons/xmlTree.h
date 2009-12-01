#ifndef _XML_TREE_H_
#define _XML_TREE_H_

#include "Singleton.h"
#include "ticpp.h"

#include "xmlTmpl.h"
#include "xmlBranch/xmlBranch.h"

#include <string>

class xmlTree : public Singleton< xmlTree >
{
public:
	xmlTree();
	~xmlTree();

	//инициализация
	void Init( std::string _sFileName );

	//завершение работы
	void Close();

private:
	//инициализировать дочерние данные
	void InitChild( ticpp::Node* pNode );

	xmlTmpl< binBranch , xmlBranchLoad , xmlBranchSave > m_xmlBranch;	//данные о стволе

	//имя файла xml
	std::string m_sFileName;
};

#endif	//_XML_TREE_H_