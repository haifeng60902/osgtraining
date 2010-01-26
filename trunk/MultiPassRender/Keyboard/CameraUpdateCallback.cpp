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
		//�������� ������ � ��������� ������ 
		binCameraState &mCamState = CameraState::Instance().GetCameraState();

		//���������� ��������
		ProcessRotate();

		//���������� �����������
		ProcessMove();

		osg::Matrix mtTr , mtRtX , mtRtZ , mtRes;
		mtRtX.makeRotate( osg::DegreesToRadians( mCamState.m_dH - 90.0 ) , 1, 0 , 0 );
		mtRtZ.makeRotate(  osg::DegreesToRadians( mCamState.m_dR ) , 0, 0 , 1 );
		mtTr.makeTranslate( mCamState.m_dX , mCamState.m_dY , mCamState.m_dZ );	

		mtRes = mtTr * mtRtZ * mtRtX;

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

	//�������� ������ � ��������� ������ 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	mCamState.m_dR = mCamState.m_dR + mEvents.m_dX * 0.5;
	mCamState.m_dH = mCamState.m_dH + mEvents.m_dY * 0.5;

	//����������� ��������� �����
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

	//�������� ������ � ��������� ������ 
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
	//����������� ������ �����

	//�������� ������ � ��������� ������ 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	double dZ = -cos( osg::DegreesToRadians( -mCamState.m_dH + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = nD * sin( osg::DegreesToRadians( mCamState.m_dR ) );
	double dY = nD * cos( osg::DegreesToRadians( mCamState.m_dR ) );

	mCamState.m_dX += dX * 0.01;
	mCamState.m_dY += dY * 0.01;
	mCamState.m_dZ += dZ * 0.01;
}