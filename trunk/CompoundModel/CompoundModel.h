#ifndef _COMPOUND_MODEL_H_
#define _COMPOUND_MODEL_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>

class CompoundModel : public osg::Referenced
{
public:
	CompoundModel();
	~CompoundModel();

	//вернуть узел содержащий землю
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//инициализировать корневой узел
	void InitNode();

	//создание из 1 модели нескольких копий
	void CreateBigModel( const osg::Vec3Array *_v 
		, const osg::Vec3Array *_n
		, const osg::Vec2Array *_tc0 );

	//добавить текстуру
	void AddTexture();

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_COMPOUND_MODEL_H_