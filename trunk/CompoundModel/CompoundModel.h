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

	//������� ���� ���������� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//���������������� �������� ����
	void InitNode();

	//�������� �� 1 ������ ���������� �����
	void CreateBigModel( const TransGeomNode2VertArray::tVrtDtd &_v 
		, const TransGeomNode2VertArray::tVrtDtd &_n
		, const osg::Vec2Array *_tc0 );

	//�������� ��������
	void AddTexture();

	//�������� ������ � ����
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//������� ��������, ���������� �������� ���������
	void CreateDynamicImage();

	//�������� �����
	void AddCity( osg::ref_ptr< osg::Geometry > _geom );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	osg::ref_ptr< CompoundUpdateCallback > m_rpCompoundUpdateCallback;
};

#endif	//_COMPOUND_MODEL_H_