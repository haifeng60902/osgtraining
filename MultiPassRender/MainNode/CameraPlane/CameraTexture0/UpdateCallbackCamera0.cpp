#include "UpdateCallbackCamera0.h"

#include "KeyboardState.h"
#include "CameraState.h"

#include <osg/Camera>

#include <iostream>

UpdateCallbackCamera0::UpdateCallbackCamera0()
{

}

void UpdateCallbackCamera0::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		//получить доступ к состоянию камеры 
		binCameraState &mCamState = CameraState::Instance().GetCameraState();

		osg::Matrix mtTr , mtRtX , mtRtZ , mtRes;
		mtRtX.makeRotate( osg::DegreesToRadians( mCamState.m_dH - 90.0 ) , 1, 0 , 0 );
		mtRtZ.makeRotate(  osg::DegreesToRadians( mCamState.m_dR ) , 0, 0 , 1 );
		mtTr.makeTranslate( mCamState.m_dX , mCamState.m_dY , mCamState.m_dZ );	

		mtRes = mtTr * mtRtZ * mtRtX;

		//задать явно смещение
		cam->setViewMatrix( mtRes );
	}

	traverse(node,nv);
}
