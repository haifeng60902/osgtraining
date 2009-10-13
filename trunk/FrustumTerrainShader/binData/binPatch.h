#ifndef _BIN_PATCH_H_
#define _BIN_PATCH_H_

#include <vector>
#include <map>

//описание объекта-дома
struct binHouse
{
	binHouse() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dR( 0.0 )
	{};

	//положение относительно патча
	double m_dX;
	double m_dY;

	//вращение
	double m_dR;
};

//описание объекта-дерева
struct binTree
{
	binTree() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dR( 0.0 )
		, m_dS( 0.0 )
	{};

	//положение относительно патча
	double m_dX;
	double m_dY;
	
	//вращение
	double m_dR;

	//масштабирование
	double m_dS;
};

struct binPatch
{
	//ключом является тип дерева в данном узле, а значением - сколько деревьев и их характеристики
	std::map< int , std::vector< binTree > > m_mapTree;

	//ключом является тип дома в данном узле, а значением - сколько домов и их характеристики
	std::map< int , std::vector< binHouse > > m_mapHouse;
};

#endif	//_BIN_PATCH_H_