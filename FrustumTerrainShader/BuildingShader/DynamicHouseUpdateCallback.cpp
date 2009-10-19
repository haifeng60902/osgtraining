#include "DynamicHouseUpdateCallback.h"

#include "../VisiblePatchArray.h"
#include "../PatchInfo.h"

#include <iostream>

DynamicHouseUpdateCallback::DynamicHouseUpdateCallback()
{

}

void DynamicHouseUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	m_pGroup = dynamic_cast< osg::Group* >( node );

	if ( m_pGroup )
	{
		//вернуть ссылку на массив видимых патчей
		const std::vector< dataPatch > &data_vis = VisiblePatchArray::Instance().GetVisibleArray512();

		//очистить данные с предыдущего шага
		ClearPrevStep();

		for ( int i = 0 ; i < data_vis.size() ; ++i )
		{
			unsigned char ucR , ucG;
			PatchInfo::Instance().Convert( data_vis[ i ].m_iX ,
				data_vis[ i ].m_iY , &ucR , &ucG );

			//обратиться к патчу по индексу
			binPatch &_binPatch = PatchInfo::Instance().GetBinPatch( ucR , ucG );

			//перебрать все содержимое патча и добавить его в m_mHause
			ParsePatch( _binPatch , data_vis[ i ].m_iX , data_vis[ i ].m_iY );
		}

		//заполнить вектор
		FillVector();

		if ( !m_mHause.empty() )
		{
			std::cout << m_mHause.begin()->second.size() << " ";
		}
	}

	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);
}

void DynamicHouseUpdateCallback::ClearPrevStep()
{
	//очистить данные с предыдущего шага
	m_pGroup->removeChildren( 0 , m_pGroup->getNumChildren() );
	m_mHause.clear();
	m_vHouse.clear();
}

void DynamicHouseUpdateCallback::ParsePatch( const binPatch &_binPatch , double dX , double dY )
{
	//перебрать все содержимое патча и добавить его в m_mHause
	tMapHouse::const_iterator it = _binPatch.m_mapHouse.begin();

	while( it != _binPatch.m_mapHouse.end() )
	{
		for ( int i = 0 ; i < it->second.size(); ++i )
		{
			m_mHause[ it->first ].push_back( it->second[ i ] );
			m_mHause[ it->first ].back().m_dX += dX;
			m_mHause[ it->first ].back().m_dY += dY;
		}
		++it;
	}
}

void DynamicHouseUpdateCallback::FillVector()
{
	//заполнить вектор
	if ( !m_mHause.empty() )
		for ( int i = 0 ; i < m_mHause.begin()->second.size() ; ++i )
		{
			m_vHouse.push_back( new SimplyShaderHause );
			m_vHouse.back()->SetupUniform( m_mHause.begin()->second[ i ] );
			m_pGroup->addChild( m_vHouse.back()->getRootNode().get() );
		}
	else
	{
		binHouse _house;
		m_vHouse.push_back( new SimplyShaderHause );
		m_vHouse.back()->SetupUniform( _house );
		m_pGroup->addChild( m_vHouse.back()->getRootNode().get() );
		// определение ограничивающего объема, размер земли 256км(в 1 км - 1024 метра), максимальная высота 500м

		_house.m_dX = 512.0;
		_house.m_dY = 512.0;
		m_vHouse.push_back( new SimplyShaderHause );
		m_vHouse.back()->SetupUniform( _house );
		m_pGroup->addChild( m_vHouse.back()->getRootNode().get() );
	}
}