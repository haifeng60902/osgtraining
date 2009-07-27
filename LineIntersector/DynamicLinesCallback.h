#ifndef _DYNAMIC_LINES_CALLBACK_H_
#define _DYNAMIC_LINES_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Array>
#include <osg/Group>
#include <osg/PrimitiveSet>

#include <vector>

class DynamicLinesCallback : public osg::NodeCallback
{
public:
	DynamicLinesCallback();
	~DynamicLinesCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	//инициализация узла, содержащего точки
	void InitPointsNode();
	
	//найти группу линий
	osg::ref_ptr< osg::Group > GetLinesGroup( osg::Node* node );

	//динамическое обновление положения линий
	void DinamicUpdateLines();

	//определение колизий
	void ColisionDetection();

	//получить случайное число
	float GetRand( float fScale );

	//найти массив вершин
	void FindVertexArray( osg::ref_ptr< osg::Group > group );

	//заполнить узел новыми координатами точек
	void FillPointsNode( const std::vector< osg::Vec3d > &res );

	//узел содержащий точки пересечения геометрии линиями
	osg::ref_ptr< osg::Group > m_PointsGroup;

	//координаты вершин линий
	osg::ref_ptr< osg::Vec3Array > m_LinesVertexs;

	//данные для координат точек и цветов
	osg::ref_ptr< osg::Vec3Array > m_V;
	osg::ref_ptr< osg::Vec4Array > m_C;

	osg::ref_ptr< osg::DrawArrays > m_DA;

	osg::Node *m_pNode;
};

#endif	//_DYNAMIC_LINES_CALLBACK_H_