#ifndef _DYNAMIC_GROUP_LEVEL_4096_NODE_H_
#define _DYNAMIC_GROUP_LEVEL_4096_NODE_H_

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupLevel4096Node : public osg::Referenced
{
public:
	struct Data
	{
		//геометрия патча
		osg::ref_ptr< osg::Geode > m_Geode;

		//uniform для динамического обновления
		osg::ref_ptr< osg::Uniform > m_Uniform;
	};

	DynamicGroupLevel4096Node();

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
	void FillIndexVector( std::vector< unsigned int > &m_vIndex , int sizeC );

	//создать массив вершин
	osg::ref_ptr<osg::Vec3Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//индексы, общие для всех узлов
	std::vector< unsigned int > m_vIndex;

	//корневой узел
	osg::ref_ptr< osg::Group > m_rootNode;

	//вектор геометрий
	std::vector< Data > m_vData;

	//счетчик добавляемых узлов
	int m_iCount;
};

#endif	//_DYNAMIC_GROUP_LEVEL_4096_NODE_H_