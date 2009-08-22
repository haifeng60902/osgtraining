#ifndef _TRANS_GEOM_NODE_2_VERT_ARRAY_H_
#define _TRANS_GEOM_NODE_2_VERT_ARRAY_H_

#include <osg/NodeVisitor>
#include <osg/Geometry>

#include <vector>

//��������� �� ��� ������� ������� �� ���� ����� �����
class TransGeomNode2VertArray : public osg::NodeVisitor
{
public:

	typedef std::vector< float > tVrtDtd;

	TransGeomNode2VertArray();
	~TransGeomNode2VertArray();

	//����� ���������� ��� ������� ���� � �����
	virtual void apply( osg::Node& node );

	//�������� ��������� ��������� �����
	tVrtDtd& GetVert(){ return m_vVer; };

	//��������� �� ������������ ������ ���������
	const osg::Vec3Array *GetVertex(){ return m_V3; };
	const osg::Vec3Array *GetNormals(){ return m_N3; };
	const osg::Vec2Array *GetTexCoord0(){ return m_TC0; };
private:

	//��������� ������� ��� ������������� ��������
	void ComputeNormalMatrix();

	//���������� Drawable ����
	void ProcessDrawableNode( const osg::Geometry *mtDrawable );

	//��������� ������ ������
	void FillVertexData( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//���������� ������, ���������� ������� ���� DrawArraysPrimitiveType
	void ProcessPrimitiveType( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//���������� ������, ���������� ������� �� ������� ���� DrawElementsUBytePrimitiveType
	void ProcessUByteIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//���������� ������, ���������� ������� �� ������� ���� DrawElementsUShortPrimitiveType
	void ProcessUShortIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//���������� ������, ���������� ������� �� ������� ���� DrawElementsUIntPrimitiveType
	void ProcessUIntIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );


	//���������� ������ ����
	void ProcessVertexNode( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind , GLenum mode );

	//���������� ����� GL_TRIANGLES
	void ProcessTriangles( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//���������� ����� GL_TRIANGLE_STRIP
	void ProcessTriangleStrip( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//���������� ����� GL_TRIANGLE_FAN
	void ProcessTriangleFun( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//��������� ������� � ����������� �������
	void SaveVertex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind );

	//�������� �������
	void OffsetPrevIndex( int ind );

	//���������� ������� ��� ������ GL_TRIANGLE_STRIP
	void ProcessIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind0 , int ind1 , int ind2 );
	
	//������ � ������������ ����� (x , y , z)
	tVrtDtd m_vVer;

	//������ � ������������ �������� (x , y , z)
	tVrtDtd m_vNor;

	//��������� �� ������ �������� � ����
	const osg::Vec3Array *m_n3;

	//������� ������������� ��� �������������� ������
	osg::Matrix m_Matrix;

	//������� ������������� ��� �������������� ��������
	osg::Matrix m_Matrix4Normal;

	//�������� �������� 3 ���������� �������� �� ������������ ������������� �� GL_TRIANGLE_STRIP
	int m_iPrevInd0;
	int m_iPrevInd1;
	int m_iPrevInd2;

	//////////////////////////////////////////////////////////////////////////
	//�� ������������ ������ ���������
	const osg::Vec3Array *m_V3;
	const osg::Vec3Array *m_N3;
	const osg::Vec2Array *m_TC0;
};

#endif	//_TRANS_GEOM_NODE_2_VERT_ARRAY_H_