#include "DynamicGroupUpdateCallback.h"

#include "dataPatch.h"

#include "GeometryPatch.h"
#include "GeometryTexturePatch.h"
#include "GeometryTexturePatch1.h"
#include "GeometryTexturePatch2.h"

#include <osgDB/ReadFile>

#include <iostream>
#include <fstream>

int iCount = 0;

DynamicGroupUpdateCallback::DynamicGroupUpdateCallback() : m_dAdd( 1.0 )
, m_dScale( 30.0 )
{
	// загрузить изображение
	m_ImageIndex = osgDB::readImageFile( "index.bmp" );
}

DynamicGroupUpdateCallback::~DynamicGroupUpdateCallback()
{

}

void DynamicGroupUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//сформировать массив данных о видимых патчах
	m_VisiblePatchArray.Update();

	//обновить коэффициенты из файла
	UpdateKof();

	//обновить статистику
	//UpdateStatistic();

	osg::ref_ptr< osg::Group > group = dynamic_cast< osg::Group* >( node );

	if ( group )
	{
		//вернуть ссылку на массив видимых патчей
		const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

		if ( !data_vis.empty() )
		{
			FindMax();
			//std::cout << data_vis.size() << "-" << FindMax() << " ";

			//очистить всех детей
			group->removeChildren( 0 , group->getNumChildren() );

			//перебрать все видимые узлы
			for( int i = 0 ; i < data_vis.size() ; ++i )
			{
				//сформировать геометрию
				//GeometryPatch patch( data_vis[ i ].m_iX , 
				//	data_vis[ i ].m_iY , 65 , 
				//	data_vis[ i ].m_iSize );

				osg::ref_ptr< osg::Geode > geode = new osg::Geode;

				if ( data_vis[ i ].m_iSize == 1024 )
				{
					GeometryTexturePatch1 patch( data_vis[ i ].m_iX , 
						data_vis[ i ].m_iY , 66 , 
						data_vis[ i ].m_iSize , m_ImageIndex.get()
						, 1 , -32 );

					geode->addDrawable( patch.GetGeometry().get() );
				}
				else
					if ( data_vis[ i ].m_iSize == 512 )
					{
						GeometryTexturePatch patch( data_vis[ i ].m_iX , 
							data_vis[ i ].m_iY , 65 , 
							data_vis[ i ].m_iSize , m_ImageIndex.get()
							, 1 , 30 );

						geode->addDrawable( patch.GetGeometry().get() );
					}
					else
						if ( data_vis[ i ].m_iSize == 2048 )
						{
							GeometryTexturePatch2 patch( data_vis[ i ].m_iX , 
								data_vis[ i ].m_iY , 68 , 
								data_vis[ i ].m_iSize , m_ImageIndex.get()
								, 1 , -32 );

							geode->addDrawable( patch.GetGeometry().get() );
						}
						//else
						//{
						//	std::cout << "65536 ";
						//}

				//добавить геометрию в сцену
				group->addChild( geode.get() );
			}
		}
	}
}

int DynamicGroupUpdateCallback::FindMax()
{
	//поиск максимального размера патча

	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

	int iMax = data_vis[ 0 ].m_iSize;

	for ( int i = 1 ; i < data_vis.size() ; ++i )
		if ( data_vis[ i ].m_iSize > iMax)
			iMax = data_vis[ i ].m_iSize;

	if ( iMax > 32768 )
	{
		int a = 1;
	}

	return iMax;
}

void DynamicGroupUpdateCallback::UpdateKof()
{
	//обновить коэффициенты из файла

	if ( !( iCount % 60 ) )
	{
		// поток для чтения файла
		std::ifstream m_in;

		m_in.open( "in.txt", std::ios::in);

		m_in >> m_dAdd >> m_dScale;

		m_in.close();

	}

	++iCount;
}

void DynamicGroupUpdateCallback::UpdateStatistic()
{
	//обновить статистику

	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

	if ( data_vis.size() > 0 )
	{
		std::map< int , int > _Statistic;

		//перебрать все видимые узлы
		for( int i = 0 ; i < data_vis.size() ; ++i )
			_Statistic[ data_vis[ i ].m_iSize ]++;

		if ( m_Statistic.empty() )
			m_Statistic = _Statistic;

		bool bUpdate = false;
		std::map< int , int > ::iterator it = _Statistic.begin();
		while( it != _Statistic.end() )
		{
			if ( m_Statistic[ it->first ] < it->second )
			{
				m_Statistic[ it->first ] = it->second;
				bUpdate = true;
			}

			++it;
		}

		if ( bUpdate )
		{

			std::map< int , int > ::iterator it = m_Statistic.begin();
			while( it != m_Statistic.end() )
			{
				std::cout << it->first << "-" << it->second << "\t";

				++it;
			}
			std::cout << "\n";
		}
	}
}