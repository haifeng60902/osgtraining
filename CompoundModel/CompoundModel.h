#ifndef _COMPOUND_MODEL_H_
#define _COMPOUND_MODEL_H_

#include "CompoundUpdateCallback.h"
#include "TransGeomNode2VertArray.h"

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geometry>

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
	void CreateBigModel( const TransGeomNode2VertArray::tVrtDtd &_v 
		, const TransGeomNode2VertArray::tVrtDtd &_n
		, const osg::Vec2Array *_tc0 );

	//добавить текстуру
	void AddTexture();

	//добавить шейдер в узел
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//создать картинку, содержащую смещения геометрии
	void CreateDynamicImage();

	//добавить город
	void AddCity( osg::ref_ptr< osg::Geometry > _geom );

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	osg::ref_ptr< CompoundUpdateCallback > m_rpCompoundUpdateCallback;
};

#endif	//_COMPOUND_MODEL_H_