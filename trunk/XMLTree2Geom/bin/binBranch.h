#ifndef _BIN_BRANCH_H_
#define _BIN_BRANCH_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;
typedef std::vector< tVecIndex > tVecVecIndex;

struct binBranchGeom
{
	binBranchGeom() : m_fAlfa( 0.0f)
	{};

	//координаты вершин: 3 значения на вершину
	tVecVertex m_vVertex;

	//нормаль к вершине: 3 значения на вершину
	tVecVertex m_vNormal;

	//текстурные координаты вершины: 2 значения на вершину
	tVecVertex m_vTexCoord;

	//индексы вершин для режима TRIANGLE_STRIP
	tVecVecIndex m_vvIndex;

	//значения альфа-теста
	float m_fAlfa;
};

//набор геометрий для LOD'ов
typedef std::vector< binBranchGeom > tVecBranch;

struct binBranch
{
	//LOD'ы ствола
	tVecBranch m_vBranch;

	//имя файла с текстурой ствола
	std::string m_sTexture;
};

#endif	//_BIN_BRANCH_H_