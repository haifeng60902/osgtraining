#ifndef _DATA_PATCH_H_
#define _DATA_PATCH_H_

struct dataPatch
{
	dataPatch() : m_iX( 0 )
		, m_iY( 0 )
		, m_iSize( 0 )
	{};

	int m_iX;
	int m_iY;
	int m_iSize;
};

#endif	//_DATA_PATCH_H_