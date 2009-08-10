#ifndef _LEAF_XML_H_
#define _LEAF_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class LeafXML : public osg::Referenced
{
public:
	LeafXML();
	~LeafXML();

	osg::ref_ptr< osg::Geode > getLeafGeode() { return m_leafGeode.get(); }

private:
	//инициировать корневой узел данными
	void InitLeafGeode();

	//добавить текстуры
	void AddTextures();

	//настроить альфа канал
	void SetupAlfaFunc();

	//корневой узел геометрии листвы
	osg::ref_ptr< osg::Geode > m_leafGeode;
};

#endif	//_LEAF_XML_H_