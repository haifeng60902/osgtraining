#ifndef _VISIBLE_PATCH_ARRAY_H_
#define _VISIBLE_PATCH_ARRAY_H_

#include "dataPatch.h"

#include <osg/Vec3>

#include <vector>

class VisiblePatchArray
{
public:
	VisiblePatchArray();
	~VisiblePatchArray();
	
	//сформировать массив данных о видимых патчах
	void Update();

	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &GetVisibleArray(){ return m_vVisible; };

private:
	//заполнить данными корневой патч
	void FillRootPatch();

	//обработать данные о видимости патчей
	void Process();

	//определение видимости патча
	bool PatchVisible( const dataPatch &patch );

	//разбить на следующих уровень
	void ProcessPatch( const dataPatch &patch );

	//проверка расстояния
	bool DistAppropriate( const dataPatch &patch );

	//вектор данных о видимых патчах
	std::vector< dataPatch > m_vVisible;

	//данные промежуточных вычислений
	std::vector< dataPatch > m_vTemp0;
	std::vector< dataPatch > m_vTemp1;

	//положение наблюдателя
	osg::Vec3 m_Pos;
};

#endif	//_VISIBLE_PATCH_ARRAY_H_