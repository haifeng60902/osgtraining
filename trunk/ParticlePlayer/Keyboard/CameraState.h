#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "Singleton.h"
#include "binCameraState.h"

class CameraState : public Singleton< CameraState >
{
public:
	CameraState();
	~CameraState();

	//�������� ������ � ��������� ������
	binCameraState &GetCameraState(){ return m_binCameraState; };
private:
	//��������� ������
	binCameraState m_binCameraState;
};

#endif	//_CAMERA_STATE_H_