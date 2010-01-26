#include "Camera0UpdateCallback.h"

#include "KeyboardState.h"

#include <osg/Camera>

#include <iostream>

namespace
{
float fY = 0.0f;
}


Camera0UpdateCallback::Camera0UpdateCallback() : m_fMoveSpeed( 0.0 )
{
	m_v3Pos = osg::Vec3( 0.0 , 0.0 , 0.0 );
}

void Camera0UpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		//обработать вращения
		ProcessRotate();

		//обработать перемещение
		ProcessMove();

		osg::Matrix mtTr , mtRtX , mtRtZ , mtRes;
		mtRtX.makeRotate( osg::DegreesToRadians( m_v3Rot.x() - 90.0 ) , 1, 0 , 0 );
		mtRtZ.makeRotate(  osg::DegreesToRadians( m_v3Rot.z() ) , 0, 0 , 1 );
		mtTr.makeTranslate( m_v3Pos );	

		mtRes = mtTr * mtRtZ * mtRtX;

		//вывод перемещения
		//std::cout << m_v3Pos.x() << " " << m_v3Pos.y() << " "
		//	<< m_v3Pos.z() <<"\n";

		//вывод углов поворота
		//std::cout << m_v3Rot.x() << " " << m_v3Rot.y() << " "
		//	<< m_v3Rot.z() <<"\n";

		//задать явно смещение
		cam->setViewMatrix( mtRes );
	}

	traverse(node,nv);
}

void Camera0UpdateCallback::ProcessRotate()
{
	//обработать вращения

	//получить доступ к состоянию клавиатуры
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	m_v3Rot.z() = m_v3Rot.z() + mEvents.m_dX * 0.5;
	m_v3Rot.x() = m_v3Rot.x() + mEvents.m_dY * 0.5;

	//ограничение диапазона углов
	if ( m_v3Rot.x() > 360.0 )
		m_v3Rot.x() -= 360.0;
	else
		if ( m_v3Rot.x() < -360.0 )
			m_v3Rot.x() += 360.0;

	if ( m_v3Rot.z() > 360.0 )
		m_v3Rot.z() -= 360.0;
	else
		if ( m_v3Rot.z() < -360.0 )
			m_v3Rot.z() += 360.0;

}

void Camera0UpdateCallback::ProcessMove()
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

void Camera0UpdateCallback::MoveForward()
{
	//перемещение камеры вперед
	double dZ = cos( osg::DegreesToRadians( -m_v3Rot.x() + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = -nD * sin( osg::DegreesToRadians( m_v3Rot.z() ) );
	double dY = -nD * cos( osg::DegreesToRadians( m_v3Rot.z() ) );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.01;
	m_v3Pos.z() += dZ * 0.01;
}

void Camera0UpdateCallback::MoveBackward()
{
	//перемещение камеры назад
	double dZ = -cos( osg::DegreesToRadians( -m_v3Rot.x() + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = nD * sin( osg::DegreesToRadians( m_v3Rot.z() ) );
	double dY = nD * cos( osg::DegreesToRadians( m_v3Rot.z() ) );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.01;
	m_v3Pos.z() += dZ * 0.01;
}