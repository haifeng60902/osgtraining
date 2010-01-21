#include "CameraUpdateCallback.h"

#include "KeyboardState.h"

#include <osg/Camera>

#include <iostream>

float fY = 0.0f;

CameraUpdateCallback::CameraUpdateCallback() : m_fMoveSpeed( 0.0 )
{
	m_v3Pos = osg::Vec3( 0.0 , -1.0 , 0.0 );
}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		//���������� ��������
		//ProcessRotate();

		//���������� �����������
		ProcessMove();

		osg::Matrix mtTr , mtRtX , mtRtZ , mtRes;
		mtRtX.makeRotate( osg::DegreesToRadians( m_v3Rot.x() - 90.0 ) , 1, 0 , 0 );
		mtRtZ.makeRotate(  osg::DegreesToRadians( m_v3Rot.z() + 180.0 ) , 0, 0 , 1 );
		mtTr.makeTranslate( m_v3Pos );	

		mtRes = mtTr * mtRtZ * mtRtX;

		std::cout << m_v3Pos.y() << "\n";

		//������ ���� ��������
		cam->setViewMatrix( mtRes );
	}

	traverse(node,nv);
}

void CameraUpdateCallback::ProcessRotate()
{
	//���������� ��������

	//�������� ������ � ��������� ����������
	binEvents &mEvents = KeyboardState::Instance().GetEvents();

	m_v3Rot.z() = m_v3Rot.z() + mEvents.m_dX * 0.5;
	m_v3Rot.x() = m_v3Rot.x() + mEvents.m_dY * 0.5;

	//����������� ��������� �����
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
			MoveBackward();
}

void CameraUpdateCallback::MoveForward()
{
	//����������� ������ ������
	double dZ = cos( osg::DegreesToRadians( -m_v3Rot.x() + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = -nD * sin( osg::DegreesToRadians( m_v3Rot.z() + 180.0 ) );
	double dY = -nD * cos( osg::DegreesToRadians( m_v3Rot.z() + 180.0 ) );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.0000001;
	m_v3Pos.z() += dZ * 0.01;
}

void CameraUpdateCallback::MoveBackward()
{
	//����������� ������ �����
	double dZ = -cos( osg::DegreesToRadians( -m_v3Rot.x() + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = nD * sin( osg::DegreesToRadians( m_v3Rot.z() + 180.0 ) );
	double dY = nD * cos( osg::DegreesToRadians( m_v3Rot.z() + 180.0 ) );

	m_v3Pos.x() += dX * 0.01;
	m_v3Pos.y() += dY * 0.0000001;
	m_v3Pos.z() += dZ * 0.01;
}