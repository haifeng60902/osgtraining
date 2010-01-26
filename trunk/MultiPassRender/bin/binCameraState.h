#ifndef _BIN_CAMERA_STATE_H_
#define _BIN_CAMERA_STATE_H_

struct binCameraState
{
	binCameraState() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dZ( 0.0 )
		, m_dH( 0.0 )
		, m_dP( 0.0 )
		, m_dR( 0.0 )
	{};

	//положение камеры в пространстве
	double m_dX;
	double m_dY;
	double m_dZ;

	//вращение камеры
	double m_dH;
	double m_dP;
	double m_dR;
};

#endif	//_BIN_CAMERA_STATE_H_