#ifndef _BRANCH_XML_CALLBACK_H_
#define _BRANCH_XML_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/PrimitiveSet>

#include <vector>

class BranchXMLCallback : public osg::NodeCallback
{
public:
	BranchXMLCallback();
	~BranchXMLCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//изменить количество индексов
	void ChangeNumIndex();

	//максимальное количество элементов
	int m_iMaxInd;

	osg::DrawElementsUShort *m_pDE;

	std::vector< unsigned short > m_usV;
};

#endif	//_BRANCH_XML_CALLBACK_H_