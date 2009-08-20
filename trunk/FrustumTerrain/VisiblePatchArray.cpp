#include "VisiblePatchArray.h"

#include "FrustumSingleton.h"

VisiblePatchArray::VisiblePatchArray()
{

}

VisiblePatchArray::~VisiblePatchArray()
{

}

void VisiblePatchArray::Update()
{
	//сформировать массив данных о видимых патчах

	//очищаем результат предыдущих вычислений
	m_vVisible.clear();

	//заполнить данными корневой патч
	FillRootPatch();

	//обработать данные о видимости патчей
	Process();
}

void VisiblePatchArray::FillRootPatch()
{
	//заполнить данными корневой патч
	dataPatch patch;
	patch.m_iSize = 512 * 256;	//размер 1 патча в метрах, (m_iX и m_iY равны 0 по умолчанию)
	m_vTemp0.push_back( patch );	//запомнить 1 патч

	patch.m_iX = 512 * 256;
	m_vTemp0.push_back( patch );	//запомнить 2 патч

	patch.m_iY = 512 * 256;
	m_vTemp0.push_back( patch );	//запомнить 3 патч

	patch.m_iX = 0;
	m_vTemp0.push_back( patch );	//запомнить 4 патч
}

void VisiblePatchArray::Process()
{
	//обработать данные о видимости патчей
	while( !m_vTemp0.empty() )
	{
		for ( int i = 0 ; i < m_vTemp0.size() ; ++i )
		{
			//определение видимости патча
			if ( PatchVisible( m_vTemp0[ i ] ) )
				//разбить на следующих уровень
				ProcessPatch( m_vTemp0[ i ] );
		}

		//очистить вектор
		m_vTemp0.clear();

		//поменять местами
		m_vTemp0.swap( m_vTemp1 );
	}
}

bool VisiblePatchArray::PatchVisible( const dataPatch &patch )
{
	//определение видимости патча
	return FrustumSingleton::Instance().BoxVisible( osg::Vec3( patch.m_iX , patch.m_iY , 0 ) , 
		osg::Vec3( patch.m_iX + patch.m_iSize , patch.m_iY + patch.m_iSize , 3000 ) );
}

void VisiblePatchArray::ProcessPatch( const dataPatch &patch )
{
	//разбить на следующих уровень
	if ( patch.m_iSize == 1024 )
	{
		//это последний уровень, записать в список патчей на отображение
		m_vVisible.push_back( patch );
		return;
	}

	dataPatch downPatch;
	downPatch.m_iX = patch.m_iX;
	downPatch.m_iY = patch.m_iY;
	downPatch.m_iSize = patch.m_iSize / 2;
	m_vTemp1.push_back( downPatch );	//1 патч

	downPatch.m_iX = patch.m_iX + downPatch.m_iSize;
	m_vTemp1.push_back( downPatch );	//2 патч

	downPatch.m_iY = patch.m_iY + downPatch.m_iSize;
	m_vTemp1.push_back( downPatch );	//3 патч

	downPatch.m_iX = patch.m_iX;
	m_vTemp1.push_back( downPatch );	//4 патч
}