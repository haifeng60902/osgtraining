#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "Singleton.h"
#include "binCameraState.h"

class CameraState : public Singleton< CameraState >
{
public:
	CameraState();
	~CameraState();

	//получить доступ к состоянию камеры
	binCameraState &GetCameraState(){ return m_binCameraState; };
private:
	//состояние камеры
	binCameraState m_binCameraState;
};

#endif	//_CAMERA_STATE_H_