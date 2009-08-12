#ifndef _DATA_BRANCH_H_
#define _DATA_BRANCH_H_

#include <vector>
#include <string>

//проверка
struct dataBranch
{
	dataBranch() : m_fAlphaTestValue( 0.0f )
	{};

	float m_fAlphaTestValue;			//значение альфа теста
	std::string m_sTexture;				//текстура ствола
	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие стволу (по 4 float компонента на вершину, x-y-z-WindWeights)
	std::vector< float > m_vNormals;	//нормали	(по 4 float компонента на вершину ,x-y-z-WindMatrixIndices)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 2 float компонента на вершину ,x-y)

	std::vector< std::vector< unsigned short > > m_Strips; //NumStrips TRIANGLE_STRIP индексов
};

#endif	//_DATA_BRANCH_H_