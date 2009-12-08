#ifndef _BIN_FRONDS_H_
#define _BIN_FRONDS_H_

#include <vector>
#include <string>

typedef std::vector< float > tVecVertex;
typedef std::vector< unsigned short > tVecIndex;
typedef std::vector< tVecIndex > tVecVecIndex;

struct binFrondsGeom
{
	binFrondsGeom() : m_fAlfa( 0.0f)
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
typedef std::vector< binFrondsGeom > tVecFronds;

struct binFronds
{
	//LOD'ы ствола
	tVecFronds m_vFronds;

	//имя файла с текстурой ствола
	std::string m_sTexture;
};


#endif	//_BIN_FRONDS_H_