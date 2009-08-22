#ifndef _TRANS_GEOM_NODE_2_VERT_ARRAY_H_
#define _TRANS_GEOM_NODE_2_VERT_ARRAY_H_

#include <osg/NodeVisitor>
#include <osg/Geometry>

#include <vector>

//наследуем от для полного прохода по всем узлам сцены
class TransGeomNode2VertArray : public osg::NodeVisitor
{
public:

	typedef std::vector< float > tVrtDtd;

	TransGeomNode2VertArray();
	~TransGeomNode2VertArray();

	//метод вызывается для каждого узла в сцене
	virtual void apply( osg::Node& node );

	//получить результат обработки узлов
	tVrtDtd& GetVert(){ return m_vVer; };

	//получение не обработанных данных геометрии
	const osg::Vec3Array *GetVertex(){ return m_V3; };
	const osg::Vec3Array *GetNormals(){ return m_N3; };
	const osg::Vec2Array *GetTexCoord0(){ return m_TC0; };
private:

	//вычислить матрицу для трансформации нормалей
	void ComputeNormalMatrix();

	//Обработать Drawable узел
	void ProcessDrawableNode( const osg::Geometry *mtDrawable );

	//заполнить вектор вершин
	void FillVertexData( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//обработать массив, содержащий вершины типа DrawArraysPrimitiveType
	void ProcessPrimitiveType( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//обработать массив, содержащий индексы на вершины типа DrawElementsUBytePrimitiveType
	void ProcessUByteIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//обработать массив, содержащий индексы на вершины типа DrawElementsUShortPrimitiveType
	void ProcessUShortIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );

	//обработать массив, содержащий индексы на вершины типа DrawElementsUIntPrimitiveType
	void ProcessUIntIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set );


	//обработать данные узла
	void ProcessVertexNode( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind , GLenum mode );

	//обработать режим GL_TRIANGLES
	void ProcessTriangles( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//обработать режим GL_TRIANGLE_STRIP
	void ProcessTriangleStrip( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//обработать режим GL_TRIANGLE_FAN
	void ProcessTriangleFun( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind );

	//запомнить вершину в формируемом массиве
	void SaveVertex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind );

	//сместить индексы
	void OffsetPrevIndex( int ind );

	//обработать индексы для режима GL_TRIANGLE_STRIP
	void ProcessIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind0 , int ind1 , int ind2 );
	
	//вектор с координатами точек (x , y , z)
	tVrtDtd m_vVer;

	//вектор с координатами нормалей (x , y , z)
	tVrtDtd m_vNor;

	//указатель на массив нормалей в узле
	const osg::Vec3Array *m_n3;

	//матрица трансформации для преобразования вершин
	osg::Matrix m_Matrix;

	//матрица трансформации для преобразования нормалей
	osg::Matrix m_Matrix4Normal;

	//значения индексов 3 предыдущих операций по формированию треугольников из GL_TRIANGLE_STRIP
	int m_iPrevInd0;
	int m_iPrevInd1;
	int m_iPrevInd2;

	//////////////////////////////////////////////////////////////////////////
	//не обработанные данные геометрии
	const osg::Vec3Array *m_V3;
	const osg::Vec3Array *m_N3;
	const osg::Vec2Array *m_TC0;
};

#endif	//_TRANS_GEOM_NODE_2_VERT_ARRAY_H_