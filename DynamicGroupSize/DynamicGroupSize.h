#ifndef _DYNAMIC_GROUP_SIZE_H_
#define _DYNAMIC_GROUP_SIZE_H_

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupSize : public osg::Referenced
{
public:
	DynamicGroupSize();
	~DynamicGroupSize();

	//вернуть узел содержащий геометрию
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//инициализировать корневой узел
	void InitNode();
	
	//добавить текстуру
	void AddTexture();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	std::vector< osg::ref_ptr< osg::Geode > > m_vecGeode;
};

#endif	//_DYNAMIC_GROUP_SIZE_H_