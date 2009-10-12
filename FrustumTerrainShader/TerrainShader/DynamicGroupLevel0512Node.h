#ifndef _DYNAMIC_GROUP_LEVEL_0512_NODE_H_
#define _DYNAMIC_GROUP_LEVEL_0512_NODE_H_

#include "dataVisPatch.h"

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupLevel0512Node : public osg::Referenced
{
public:
	
	DynamicGroupLevel0512Node();

	//вернуть узел содержащий землю
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

	//удалить всех потомков корневого узла
	void ResetRootNode();

	//добавить патч геометрии из буффера в корневой узел
	void AddPatch( float x , float y );

	//вывести количество узлов для отрисовки
	void PrintSize();

private:

	//инициализировать геометрию патчей земной поверхности
	void InitGeodes();

	//добавить геометрию в i'ый узел
	void AddGeometry( int i );

	//настроить параметры необходимые в шейдере
	void SetupShaderParam( int i );

	//заполнить вектор индексами
	void FillIndexVector( std::vector< unsigned short > &m_vIndex , int sizeC );

	//создать массив вершин
	osg::ref_ptr<osg::Vec4Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//вектор геометрий
	std::vector< dataVisPatch > m_vData;

	//счетчик добавляемых узлов
	int m_iCount;
};

#endif	//_DYNAMIC_GROUP_LEVEL_0512_NODE_H_