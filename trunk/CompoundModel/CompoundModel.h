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

	//������� ���� ���������� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:

	//���������������� �������� ����
	void InitNode();

	//�������� �� 1 ������ ���������� �����
	void CreateBigModel( const osg::Vec3Array *_v 
		, const osg::Vec3Array *_n
		, const osg::Vec2Array *_tc0 );

	//�������� ��������
	void AddTexture();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;
};

#endif	//_COMPOUND_MODEL_H_