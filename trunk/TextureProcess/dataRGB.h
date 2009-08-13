#ifndef _DATA_RGB_H_
#define _DATA_RGB_H_

struct dataRGB
{
	dataRGB() : m_ucR( 0 )
		, m_ucG( 0 )
		, m_ucB( 0 )
	{};

	bool operator != ( const dataRGB &_data ) const
	{
		if ( ( m_ucR != _data.m_ucR )
			|| ( m_ucG != _data.m_ucG )
			|| ( m_ucB != _data.m_ucB ) )
			return true;

		return false;
	}

	bool operator < ( const dataRGB &_data ) const
	{
		unsigned int _hashOrig = m_ucR * 65536 + m_ucG * 256 + m_ucB;
		unsigned int _hashData = _data.m_ucR * 65536 + _data.m_ucG * 256 + _data.m_ucB;

		return _hashOrig < _hashData;
	}

	unsigned char m_ucR;
	unsigned char m_ucG;
	unsigned char m_ucB;
};

#endif	_DATA_RGB_H_