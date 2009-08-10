#ifndef _DATA_LEAF_H_
#define _DATA_LEAF_H_

#include <vector>
#include <string>

struct dataLeaf
{
	dataLeaf() : m_fAlphaTestValue( 0.0f )
		, m_fFreqY( 0.0f )
		, m_fAmplY( 0.0f )
		, m_fFreqZ( 0.0f )
		, m_fAmplZ( 0.0f )
	{};

	float m_fAlphaTestValue;				//значение альфа теста
	std::vector< std::string > m_vTextures;	//текстуры веток
	std::vector< float > m_vCoords;		//координаты вершин, принадлежащие веткам (по 3 float компонента на вершину, x-y-z)
	std::vector< float > m_vNormals;	//нормали	(по 3 float компонента на вершину ,x-y-z)
	std::vector< float > m_vTexCoords0;	//текстурные координаты (по 4 float компонента на вершину ,s-t-weight-matrix index)
	std::vector< float > m_vTexCoords1;	//текстурные координаты (по 3 float компонента на вершину ,size_x - size_y - map_index )
	float m_fFreqY;						//частота вращения листвы вокруг оси Y
	float m_fAmplY;						//амплитуда вращения листвы вокруг оси Y
	float m_fFreqZ;						//частота вращения листвы вокруг оси Z
	float m_fAmplZ;						//амплитуда вращения листвы вокруг оси Z
};

#endif	//_DATA_LEAF_H_