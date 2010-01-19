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
		//���������� ��������
		ProcessRotate();

		//���������� �����������
		ProcessMove();

		osg::Matrix mtTr , mtRtX , mtRtY;
		mtRtX.makeRotate( osg::DegreesToRadians( m_v3Rot.x() ) , 1, 0 , 0 );
		mtRtY.makeRotate(  osg::DegreesToRadians( m_v3Rot.y() ) , 0, 1 , 0 );
		mtTr.makeTranslate( m_v3Pos );	

		//������ ���� ��������
		cam->setViewMatrix( mtTr * mtRtY * mtRtX );
	}

	traverse(node,nv);
}

void CameraUpdateCallback::ProcessRotate()
{
	//���������� ��������

	//�������� ������ � ��������� ����������
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	m_v3Rot.y() = m_v3Rot.y() + mEvents.m_dX * 0.5;
	m_v3Rot.x() = m_v3Rot.x() - mEvents.m_dY * 0.5;

	//����������� ��������� �����
	if ( m_v3Rot.x() > 360.0 )
		m_v3Rot.x() -= 360.0;
	else
		if ( m_v3Rot.x() < -360.0 )
			m_v3Rot.x() += 360.0;

	if ( m_v3Rot.y() > 360.0 )
		m_v3Rot.y() -= 360.0;
	else
		if ( m_v3Rot.y() < -360.0 )
			m_v3Rot.y() += 360.0;

}

void CameraUpdateCallback::ProcessMove()
{
	//���������� �����������

	//�������� ������ � ��������� ����������
	binEvents &mEvents = KeyboardState::Instance().GetEvents();
	if ( mEvents.m_bLeft )
		//����������� ������ ������
		MoveForward();
	else
		if ( mEvents.m_bRight )
			//����������� ������ �����
			MoveForward();
}

void CameraUpdateCallback::MoveForward()
{
	//����������� ������ ������
	double dY = -sin( osg::DegreesToRadians( m_v3Rot.x() ) );
	double nD = sqrt( 1.0 - dY * dY );

	double dX = nD * sin( m_v3Rot.y() );
	double dZ = -nD * cos( m_v3Rot.y() );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.01;
	m_v3Pos.z() += dZ * 0.01;
}

void CameraUpdateCallback::MoveBackward()
{
	//����������� ������ �����
	double dY = sin( osg::DegreesToRadians( m_v3Rot.x() ) );
	double nD = sqrt( 1.0 - dY * dY );

	double dX = -nD * sin( m_v3Rot.y() );
	double dZ = nD * cos( m_v3Rot.y() );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.01;
	m_v3Pos.z() += dZ * 0.01;
}