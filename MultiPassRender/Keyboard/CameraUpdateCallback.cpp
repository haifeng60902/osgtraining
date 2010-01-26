#include "CameraUpdateCallback.h"

#include "KeyboardState.h"
#include "CameraState.h"

#include <osg/Camera>

#include <iostream>

CameraUpdateCallback::CameraUpdateCallback() : m_fMoveSpeed( 0.0 )
{
	
}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		//получить доступ к состоянию камеры 
		binCameraState &mCamState = CameraState::Instance().GetCameraState();

		//обработать вращения
		ProcessRotate();

		//обработать перемещение
		ProcessMove();

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

void CameraUpdateCallback::ProcessRotate()
{
	//обработать вращения

	//получить доступ к состоянию клавиатуры
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	//получить доступ к состоянию камеры 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	mCamState.m_dR = mCamState.m_dR + mEvents.m_dX * 0.5;
	mCamState.m_dH = mCamState.m_dH + mEvents.m_dY * 0.5;

	//ограничение диапазона углов
	if ( mCamState.m_dH > 360.0 )
		mCamState.m_dH -= 360.0;
	else
		if ( mCamState.m_dH < -360.0 )
			mCamState.m_dH += 360.0;

	if ( mCamState.m_dR > 360.0 )
		mCamState.m_dR -= 360.0;
	else
		if ( mCamState.m_dR < -360.0 )
			mCamState.m_dR += 360.0;

}

void CameraUpdateCallback::ProcessMove()
{
	//обработать перемещение

	//получить доступ к состоянию клавиатуры
	binEvents &mEvents = KeyboardState::Instance().GetEvents();
	if ( mEvents.m_bLeft )
		//перемещение камеры вперед
		MoveForward();
	else
		if ( mEvents.m_bRight )
			//перемещение камеры назад
			MoveBackward();
}

void CameraUpdateCallback::MoveForward()
{
	//перемещение камеры вперед

	//получить доступ к состоянию камеры 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	double dZ = cos( osg::DegreesToRadians( -mCamState.m_dH + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = -nD * sin( osg::DegreesToRadians( mCamState.m_dR ) );
	double dY = -nD * cos( osg::DegreesToRadians( mCamState.m_dR ) );

	mCamState.m_dX += dX * 0.01;
	mCamState.m_dY += dY * 0.01;
	mCamState.m_dZ += dZ * 0.01;
}

void CameraUpdateCallback::MoveBackward()
{
	//перемещение камеры назад

	//получить доступ к состоянию камеры 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	double dZ = -cos( osg::DegreesToRadians( -mCamState.m_dH + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = nD * sin( osg::DegreesToRadians( mCamState.m_dR ) );
	double dY = nD * cos( osg::DegreesToRadians( mCamState.m_dR ) );

	mCamState.m_dX += dX * 0.01;
	mCamState.m_dY += dY * 0.01;
	mCamState.m_dZ += dZ * 0.01;
}