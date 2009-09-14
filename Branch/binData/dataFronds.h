#ifndef _DATA_FRONDS_H_
#define _DATA_FRONDS_H_

#include <vector>
#include <string>

struct dataFrLOD
{
	dataFrLOD() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;				//значение альфа теста

	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие веткам (по 3 float компонента на вершину, x-y-z)
	std::vector< float > m_vNormals;	//нормали	(по 3 float компонента на вершину ,x-y-z)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 4 float компонента на вершину ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP индексов
};

struct dataFronds
{
	dataFronds() //: m_fAlphaTestValue( 0.0f )
	{};

//	float m_fAlphaTestValue;				//значение альфа теста
	std::vector< std::string > m_vTextures;	//текстуры веток

	/*
	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие веткам (по 3 float компонента на вершину, x-y-z)
	std::vector< float > m_vNormals;	//нормали	(по 3 float компонента на вершину ,x-y-z)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 4 float компонента на вершину ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP индексов
	*/

	//данные геометрии LOD'ов веток
	std::vector< dataFrLOD > m_vFrLOD;
};

#endif	//_DATA_FRONDS_H_