#include "DynamicHouseUpdateCallback.h"

#include "../VisiblePatchArray.h"
#include "../PatchInfo.h"

DynamicHouseUpdateCallback::DynamicHouseUpdateCallback()
{

}

void DynamicHouseUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &data_vis = VisiblePatchArray::Instance().GetVisibleArray512();

	//очистить информацию с предыдущего шага
	m_mHause.clear();

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

	if ( !m_mHause.empty() && m_mHause.begin()->second.size() > 10 )
	{
		int a = 1;
	}

	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);
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
