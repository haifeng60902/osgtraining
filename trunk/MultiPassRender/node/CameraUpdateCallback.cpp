#include "CameraUpdateCallback.h"

#include "KeyboardState.h"

#include <osg/Camera>

#include <iostream>

float fY = 0.0f;

CameraUpdateCallback::CameraUpdateCallback() : m_fMoveSpeed( 0.0 )
{

}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		osg::Matrix mtTr , mtRtX , mtRtZ;
		mtRtX.makeRotate( osg::DegreesToRadians( -90.0 ) , 1, 0 , 0 );
		//mtRtZ.makeRotate(  osg::DegreesToRadians( -60.0 ) , 0, 0 , 1 );
		mtRtZ.makeRotate(  fY , 0, 0 , 1 );
		mtTr.makeTranslate( 0 , 0 , -15 );	

		fY -= 0.01;

		//std::cout << fY << " ";

		//задать явно смещение
		cam->setViewMatrix( mtRtZ * mtRtX * mtTr );
	}

	traverse(node,nv);
}

void CameraUpdateCallback::ProcessKeyboard()
{
	//обработать состояние клавиатуры

	//получить доступ к состоянию клавиатуры
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	m_v3Rot.z() = m_v3Rot.z() + mEvents.m_dX * 10.0;
	m_v3Rot.x() = m_v3Rot.x() + mEvents.m_dY * 10.0;

	//ограничение диапазона углов
	if ( m_v3Rot.x() > 360.0 )
		m_v3Rot.x() -= 360.0;
	else
		if ( m_v3Rot.x() < -360.0 )
			m_v3Rot.x() += 360.0;
}