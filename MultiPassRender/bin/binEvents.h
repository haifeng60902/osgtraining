#ifndef _BIN_EVENTS_H_
#define _BIN_EVENTS_H_

struct binEvents
{
	binEvents()
	{
		memset( m_bKey , 0 , sizeof( m_bKey ) );
	};

	//состояние нажатия клавиш
	bool m_bKey[ 256 ];
};

#endif	//_BIN_EVENTS_H_