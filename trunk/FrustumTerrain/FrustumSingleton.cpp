#include "FrustumSingleton.h"

FrustumSingleton::FrustumSingleton()
{
	//создать и выделить память под 8 точек, определяющих view frustum
	vOrig = new osg::Vec3Array;
	vTrans = new osg::Vec3Array;
	vOrig->resize( 8 );
	vTrans->resize( 8 );
}

FrustumSingleton::~FrustumSingleton()
{

}

void FrustumSingleton::UpdateProjection( osg::Matrix proj )
{
	//обновить информацию матрицы проекции
	//Get near and far from the Projection matrix.
	float near = proj(3,2) / (proj(2,2)-1.0);
	float far = proj(3,2) / (1.0+proj(2,2));

	// Get the sides of the near plane.
	float nLeft = near * (proj(2,0)-1.0) / proj(0,0);
	float nRight = near * (1.0+proj(2,0)) / proj(0,0);
	float nTop = near * (1.0+proj(2,1)) / proj(1,1);
	float nBottom = near * (proj(2,1)-1.0) / proj(1,1);

	// Get the sides of the far plane.
	float fLeft = far * (proj(2,0)-1.0) / proj(0,0);
	float fRight = far * (1.0+proj(2,0)) / proj(0,0);
	float fTop = far * (1.0+proj(2,1)) / proj(1,1);
	float fBottom = far * (proj(2,1)-1.0) / proj(1,1);
	
	//заполнение массива вершин, определяющих view frustum
	(*vOrig)[0].set( nLeft, nBottom, -near );
	(*vOrig)[1].set( nRight, nBottom, -near );
	(*vOrig)[2].set( nRight, nTop, -near );
	(*vOrig)[3].set( nLeft, nTop, -near );
	(*vOrig)[4].set( fLeft, fBottom, -far );
	(*vOrig)[5].set( fRight, fBottom, -far );
	(*vOrig)[6].set( fRight, fTop, -far );
	(*vOrig)[7].set( fLeft, fTop, -far );
}

void FrustumSingleton::UpdateFrustum( osg::Matrix inv_mv )
{
	//обновить плоскости отсечения камеры
	(*vTrans)[0] = (*vOrig)[0] * inv_mv;
	(*vTrans)[1] = (*vOrig)[1] * inv_mv;
	(*vTrans)[2] = (*vOrig)[2] * inv_mv;
	(*vTrans)[3] = (*vOrig)[3] * inv_mv;
	(*vTrans)[4] = (*vOrig)[4] * inv_mv;
	(*vTrans)[5] = (*vOrig)[5] * inv_mv;
	(*vTrans)[6] = (*vOrig)[6] * inv_mv;
	(*vTrans)[7] = (*vOrig)[7] * inv_mv;

	//вычислить плоскости отсечения
	CalcClipPlanes();
}

void FrustumSingleton::CalcClipPlanes()
{
	//вычислить плоскости отсечения

	//левая плоскость отсечения
	plane[0] = MakePlane( (*vTrans)[0] , (*vTrans)[7] , (*vTrans)[3] );

	//правая плоскость отсечения
	plane[1] = MakePlane( (*vTrans)[1] , (*vTrans)[2] , (*vTrans)[6] );

	//верхняя плоскость
	plane[2] = MakePlane( (*vTrans)[2] , (*vTrans)[3] , (*vTrans)[7] );

	//нижняя плоскость
	plane[3] = MakePlane( (*vTrans)[0] , (*vTrans)[1] , (*vTrans)[4] );

	//ближняя плоскость
	plane[4] = MakePlane( (*vTrans)[0] , (*vTrans)[2] , (*vTrans)[1] );

	//дальняя плоскость
	plane[5] = MakePlane( (*vTrans)[5] , (*vTrans)[6] , (*vTrans)[7] );
}

osg::Vec4 FrustumSingleton::MakePlane( osg::Vec3 P1 , osg::Vec3 P2 , osg::Vec3 P3 )
{
	//вычислить уравнение плоскости по трем точкам
	osg::Vec4 plane;

	//  A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2)
	plane.x() = P1.y() * ( P2.z() - P3.z() ) + P2.y() * ( P3.z() - P1.z() ) + P3.y() * ( P1.z() - P2.z() );

	//	B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2) 
	plane.y() = P1.z() * ( P2.x() - P3.x() ) + P2.z() * ( P3.x() - P1.x() ) + P3.z() * ( P1.x() - P2.x() );

	//	C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)
	plane.z() = P1.x() * ( P2.y() - P3.y() ) + P2.x() * ( P3.y() - P1.y() ) + P3.x() * ( P1.y() - P2.y() );

	//	- D = x1 (y2 z3 - y3 z2) + x2 (y3 z1 - y1 z3) + x3 (y1 z2 - y2 z1)
	plane.w() = -P1.x() * ( P2.y() * P3.z() - P3.y() * P2.z() ) 
		- P2.x() * ( P3.y() * P1.z() - P1.y() * P3.z() )
		- P3.x() * ( P1.y() * P2.z() - P2.y() * P1.z() );

	return plane;
}

bool FrustumSingleton::BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx )
{
	//Определение видимости BOX'a
	for( int i = 0 ; i < 6 ; i++ )
	{
		if( plane[i] * osg::Vec4( minn.x() , minn.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , minn.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , maxx.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , maxx.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , minn.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , minn.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , maxx.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , maxx.y() , maxx.z() , 1.0 ) > 0.0 ) continue;

		return false;
	}
	return true;
}
