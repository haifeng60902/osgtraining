#ifndef _BIN_BRANCH_H_
#define _BIN_BRANCH_H_

#include <vector>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;

struct binBranchGeom
{
	//координаты вершин: 3 значения на вершину
	tVecVertex m_vVertex;

	//нормаль к вершине: 3 значения на вершину
	tVecVertex m_vNormal;

	//текстурные координаты вершины: 2 значения на вершину
	tVecVertex m_vTexCoord;

	//индексы вершин для режима TRIANGLE_STRIP
	tVecIndex m_vIndex;
};

//набор геометрий для LOD'ов
typedef std::vector< binBranchGeom > tVecBranch;

struct binBranch
{
	//LOD'ы ствола
	tVecBranch m_vBranch;
};

#endif	//_BIN_BRANCH_H_