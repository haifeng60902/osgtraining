#ifndef _BIN_EVENTS_H_
#define _BIN_EVENTS_H_

#include <memory>

struct binEvents
{
	binEvents() : m_dX( 0.0 )
		, m_dY( 0.0 )
		, m_bRight( false )
		, m_bLeft( false )
		, m_bMiddle( false )
	{
		memset( m_bKey , 0 , sizeof( m_bKey ) );
	};

	//состояние нажатия клавиш
	bool m_bKey[ 256 ];

	//положение мыши относительно окна ( -1 .. +1 )
	double m_dX;
	double m_dY;

	//состояния нажатия кнопок мыши
	bool m_bLeft;
	bool m_bRight;
	bool m_bMiddle;
};

#endif	//_BIN_EVENTS_H_