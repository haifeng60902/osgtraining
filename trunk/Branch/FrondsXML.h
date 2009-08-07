#ifndef _FRONDS_XML_H_
#define _FRONDS_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class FrondsXML : public osg::Referenced
{
public:
	FrondsXML();
	~FrondsXML();

	osg::ref_ptr< osg::Geode > getFrondsGeode() { return m_frondsGeode.get(); }

private:
	//инициировать корневой узел данными
	void InitFrondsGeode();

	//добавить текстуру
	void AddTexture();

	//настроить альфа канал
	void SetupAlfaFunc();

	//корневой узел геометрии веток
	osg::ref_ptr< osg::Geode > m_frondsGeode;
};

#endif	//_FRONDS_XML_H_