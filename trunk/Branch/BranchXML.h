#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Group>

class BranchXML : public osg::Referenced
{
public:
	BranchXML();
	~BranchXML();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	//инициировать корневой узел данными
	void InitRootNode();

	//добавить текстуру
	void AddTexture();

	//настроить альфа канал
	void SetupAlfaFunc();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_BRANCH_XML_H_