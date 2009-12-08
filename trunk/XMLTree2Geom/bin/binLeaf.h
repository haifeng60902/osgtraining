#ifndef _BIN_LEAF_H_
#define _BIN_LEAF_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;

struct binLeafGeom
{
	binLeafGeom() : m_fAlfa( 0.0f )
	{};

	//координаты вершин: 3 значения на вершину
	tVecVertex m_vVertex;

	//нормаль к вершине: 3 значения на вершину
	tVecVertex m_vNormal;

	//текстурные координаты вершины: 2 значения на вершину
	tVecVertex m_vTexCoord;

	//смещение относительно центра вершины: 2 значения на вершину + 1 номер текстуры
	tVecVertex m_vVerOffset;

	//значения альфа-теста
	float m_fAlfa;
};

//набор геометрий для LOD'ов
typedef std::vector< binLeafGeom > tVecLeaf;

//набор текстур листвы
typedef std::vector< std::string > tVecTexture;

struct binLeaf
{
	//LOD'ы листвы
	tVecLeaf m_vLeaf;

	//имена файлов с текстурами листвы
	tVecTexture m_vTextures;
};

#endif	//_BIN_LEAF_H_