#ifndef _BIN_LIGHT_H_
#define _BIN_LIGHT_H_

struct binLight
{
	binLight() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_dZ( 0.0 )
	{};

	//положение источника света в простанстве
	double m_dX;
	double m_dY;
	double m_dZ;
};

#endif	//_BIN_LIGHT_H_