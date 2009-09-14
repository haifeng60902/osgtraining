#ifndef _DATA_BRANCH_H_
#define _DATA_BRANCH_H_

#include <vector>
#include <string>

struct dataLOD
{
	dataLOD() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;			//значение альфа теста
	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие стволу (по 3 float компонента на вершину, x-y-z)
	std::vector< float > m_vNormals;	//нормали	(по 3 float компонента на вершину ,x-y-z)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 4 float компонента на вершину ,s-t-weight-matrix index)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP индексов
};

struct dataBranch
{
	dataBranch()
	{};

	std::string m_sTexture;				//текстура ствола

	//данные геометрии LOD'ов
	std::vector< dataLOD > m_vLOD;
};

#endif	//_DATA_BRANCH_H_