#ifndef _FRUSTUM_SINGLETON_H_
#define _FRUSTUM_SINGLETON_H_

#include "Singleton.h"

#include <osg/Matrix>
#include <osg/Array>
#include <osgUtil/CullVisitor>

class FrustumSingleton : public Singleton< FrustumSingleton >
{
public:
	FrustumSingleton();
	~FrustumSingleton();

	//обновить информацию матрицы проекции
	void UpdateProjection( osg::Matrix proj );

	//обновить плоскости отсечения камеры
	void UpdateFrustum( osg::Matrix inv_mv );

	//Определение видимости BOX'a
	bool BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx );

	//задать положение наблюдателя
	void SetViewPos( osg::Vec3 pos ){ m_Pos = pos; };

	//вернуть положение наблюдателя
	osg::Vec3 GetViewPos() const { return m_Pos; };

	//задать параметры камеры
	void SetCullVis( osgUtil::CullVisitor* _CullVis ){ m_CullVis = _CullVis; };

	//проверка, задан ли osgUtil::CullVisitor
	bool IsCullVis();

	//обработать данные osgUtil::CullVisitor
	void ProcessCullVis();

private:

	//вычислить плоскости отсечения
	void CalcClipPlanes();

	//вычислить уравнение плоскости по трем точкам
	osg::Vec4 MakePlane( osg::Vec3 P1 , osg::Vec3 P2 , osg::Vec3 P3 );

	//указатель на параметры камеры
	osgUtil::CullVisitor* m_CullVis;

	//исходный массив точек
	osg::ref_ptr< osg::Vec3Array > vOrig;

	//рабочий массив точек
	osg::ref_ptr< osg::Vec3Array > vTrans;

	//шесть плоскостей, ограничивающих видимый объем
	osg::Vec4 plane[6];

	//положение наблюдателя
	osg::Vec3 m_Pos;

	//расчет матрицы проекции выполнить один раз
	bool m_bProj;
};

#endif	//_FRUSTUM_SINGLETON_H_