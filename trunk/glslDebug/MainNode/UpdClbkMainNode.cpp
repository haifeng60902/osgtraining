#include "UpdClbkMainNode.h"

#include "KeyboardState.h"
#include "CameraState.h"

#include <osg/Math>

#include <iostream>

UpdClbkMainNode::UpdClbkMainNode() : m_fMoveSpeed( 0.0 )
{

}

void UpdClbkMainNode::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//���������� ��������
	//ProcessRotate();

	//���������� �����������
	ProcessMove();

	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);  
}

void UpdClbkMainNode::ProcessRotate()
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

void UpdClbkMainNode::ProcessMove()
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

void UpdClbkMainNode::MoveForward()
{
	//����������� ������ ������

	//�������� ������ � ��������� ������ 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	double dZ = cos( osg::DegreesToRadians( -mCamState.m_dH + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = -nD * sin( osg::DegreesToRadians( mCamState.m_dR ) );
	double dY = -nD * cos( osg::DegreesToRadians( mCamState.m_dR ) );

	mCamState.m_dX += dX * 1.0;
	mCamState.m_dY += dY * 1.0;
	mCamState.m_dZ += dZ * 1.0;

	std::cout << mCamState.m_dY << " ";
}

void UpdClbkMainNode::MoveBackward()
{
	//����������� ������ �����

	//�������� ������ � ��������� ������ 
	binCameraState &mCamState = CameraState::Instance().GetCameraState();

	double dZ = -cos( osg::DegreesToRadians( -mCamState.m_dH + 90.0 ) );
	double nD = sqrt( 1.0 - dZ * dZ );

	double dX = nD * sin( osg::DegreesToRadians( mCamState.m_dR ) );
	double dY = nD * cos( osg::DegreesToRadians( mCamState.m_dR ) );

	mCamState.m_dX += dX * 1.0;
	mCamState.m_dY += dY * 1.0;
	mCamState.m_dZ += dZ * 1.0;

	std::cout << mCamState.m_dY << " ";
}
