#ifndef _DATA_FRONDS_H_
#define _DATA_FRONDS_H_

#include <vector>
#include <string>

struct dataFronds
{
	dataFronds() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;				//значение альфа теста
	std::vector< std::string > m_vTextures;	//текстуры веток
	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие веткам (по 4 float компонента на вершину, x-y-z-WindWeights)
	std::vector< float > m_vNormals;	//нормали	(по 4 float компонента на вершину ,x-y-z-WindMatrixIndices)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 2 float компонента на вершину ,x-y)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP индексов
};

#endif	//_DATA_FRONDS_H_