#include "UniUpdClbkLightPos.h"

#include "Lighting.h"
#include "CameraState.h"

UniUpdClbkLightPos::UniUpdClbkLightPos()
{

}

void UniUpdClbkLightPos::operator()( osg::Uniform* uniform, osg::NodeVisitor* nv )
{
	//получить доступ к состоянию камеры 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	osg::Matrix mtTr , mtRtX , mtRtZ , mtRes;
	mtRtX.makeRotate( osg::DegreesToRadians( mCamState.m_dH - 90.0 ) , 1, 0 , 0 );
	mtRtZ.makeRotate(  osg::DegreesToRadians( mCamState.m_dR ) , 0, 0 , 1 );
	mtTr.makeTranslate( mCamState.m_dX , mCamState.m_dY , mCamState.m_dZ );	

	mtRes = mtTr * mtRtZ * mtRtX;

	//получить положение камеры
	osg::Vec4 v4LightPos = osg::Vec4( Lighting::Instance().GetLight().m_dX , 
		Lighting::Instance().GetLight().m_dY ,
		Lighting::Instance().GetLight().m_dZ , 
		1.0 );

	v4LightPos = v4LightPos * mtRes;

	//передать новые значения положения источника света
	uniform->set( v4LightPos );
}