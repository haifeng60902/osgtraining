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

	//инициализация
	void Init( std::string _sFileName );

	//завершение работы
	void Close();

	//получить доступ к данным ствола
	binBranch &GetBranch(){ return m_xmlBranch.GetData(); };

	//получить доступ к данным веток
	binFronds &GetFronds(){ return m_xmlFronds.GetData(); };

private:
	//инициализировать дочерние данные
	void InitChild( ticpp::Node* pNode );

	xmlTmpl< binBranch , xmlBranchLoad , xmlBranchSave > m_xmlBranch;	//данные о стволе
	xmlTmpl< binFronds , xmlFrondsLoad , xmlFrondsSave > m_xmlFronds;	//данные о ветках

	//имя файла xml
	std::string m_sFileName;
};

#endif	//_XML_TREE_H_